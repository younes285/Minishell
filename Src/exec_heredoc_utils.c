/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:03:16 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 13:59:36 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	last_exec_heredoc(t_data *data, char **cmds)
{
	int		i[4];
	char	**last;

	last = (char **)malloc(sizeof(char *) * (ft_strlen_2(cmds) + 1));
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	i[3] = 0;
	last_exec_heredoc_helper(cmds, i);
	while (i[2]++, cmds[i[2]])
	{
		if (check_s_equal(cmds[i[2]], "<<") == 0
			&& (i[2] == 0 || check_s_equal(cmds[i[2] - 1], "<<") == 0)
			&& check_s_equal(cmds[i[2]], ">>") == 0
			&& (i[2] == 0 || check_s_equal(cmds[i[2] - 1], ">>") == 0))
		{
			last[i[3]] = ft_strdup((const char *)cmds[i[2]]);
			i[3]++;
		}
	}
	last_heredoc_helper(&last, cmds, i, data);
	exec_heredoc(data, last);
	data->exit_status = 0;
	free_arr(last);
}

void	exec_heredoc_skipper(t_data *data, char **cmds, int c)
{
	int		i;
	int		op;

	op = 0;
	i = 0;
	while (cmds[i] && op < c - 1)
	{
		if (check_s_equal(cmds[i], "<<"))
		{
			init_args_to_heredoc(data, i, cmds);
			op++;
		}
		i++;
	}
	last_exec_heredoc(data, cmds);
}

int	validate_cmd_syntax(char **cmds, int i[2], t_data *data, int *j)
{
	if (check_s_equal(cmds[*j], ">>") || check_s_equal(cmds[*j], "<<"))
	{
		if (cmds[*j + 1] == NULL || cmds[*j + 1][0] == '\0')
		{
			printf("bash: syntax error near unexpected token \n");
			data->exit_status = 1;
			free_arr(cmds);
			return (1);
		}
		if (check_s_equal(cmds[*j + 1], ">>")
			|| check_s_equal(cmds[*j + 1], "<<")
			|| is_operation(cmds[*j + 1][0]))
		{
			printf("bash: syntax error near unexpected token \n");
			data->exit_status = 1;
			free_arr(cmds);
			return (1);
		}
		i[1]++;
	}
	return (0);
}

void	here_condition(t_data *data, char **cmds, int *i)
{
	if ((i[0] == 1 && (i[1] == 1 || i[1] == 0))
		|| (i[1] == 1 && (i[0] == 1 || i[0] == 0)))
		exec_heredoc(data, cmds);
	else
	{
		exec_append_skipper(data, cmds);
		exec_heredoc_skipper(data, cmds, i[0]);
	}
}

void	exec_heredoc_helper(t_data *data, char *cmd)
{
	int		i[2];
	int		j;
	char	**cmds;

	cmds = ft_split_2(cmd, ' ');
	remove_quote(data, cmds);
	j = 0;
	i[0] = 0;
	i[1] = 0;
	while (cmds[j])
	{
		if (validate_cmd_syntax(cmds, i, data, &j) == 1)
			return ;
		if (check_s_equal(cmds[j], "<<"))
			i[0]++;
		else if (check_s_equal(cmds[j], ">>"))
			i[1]++;
		j++;
	}
	here_condition(data, cmds, i);
	free_arr(cmds);
}
