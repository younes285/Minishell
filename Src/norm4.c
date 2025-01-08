/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:33:47 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/01 20:05:09 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	double_unset(t_data *data, char **args)
{
	data->env = unset(args, ft_strlen_2(args), data->env, data);
	data->env2 = unset(args, ft_strlen_2(args), data->env2, data);
}

void	open_input_file(char *input, t_data *data)
{
	int	file;

	file = open(input, O_RDONLY);
	if (file == -1)
	{
		perror(input);
		data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(file);
		data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	close(file);
}

void	last_exec_heredoc_helper(char **cmds, int i[2])
{
	int	j;

	j = -1;
	while (j++, cmds[j])
	{
		if (check_s_equal(cmds[j], "<<"))
			i[0] = j;
		if (check_s_equal(cmds[j], ">>"))
			i[1] = j;
	}
}

int	copy_heredoc_parts(char ***last, char **cmds, int *i)
{
	if (cmds[i[0] + 1])
	{
		(*last)[i[3]] = ft_strdup(cmds[i[0]]);
		if (!(*last)[(i[3])])
			return (0);
		i[3]++;
		(*last)[i[3]] = ft_strdup(cmds[i[0] + 1]);
		if (!(*last)[(i[3])])
			return (0);
		i[3]++;
	}
	return (1);
}

void	last_heredoc_helper(char ***last, char **cmds, int i[4], t_data *data)
{
	if (i[0] != -1)
	{
		if (copy_heredoc_parts(last, cmds, i) == 0)
			return (exit_status_return(1, data));
	}
	if (i[1] != -1)
	{
		if (cmds[i[1] + 1])
		{
			(*last)[i[3]] = ft_strdup(cmds[i[1]]);
			if (!(*last)[i[3]])
				return (exit_status_return(1, data));
			i[3]++;
			(*last)[i[3]] = ft_strdup(cmds[i[1] + 1]);
			if (!(*last)[i[3]])
				return (exit_status_return(1, data));
			i[3]++;
		}
	}
	(*last)[i[3]] = NULL;
}
