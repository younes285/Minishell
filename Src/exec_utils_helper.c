/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:49:56 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:32:12 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_file(char **cmds, char *sign)
{
	int		i;
	char	*f;

	f = NULL;
	i = 0;
	while (cmds[i])
	{
		if (check_s_equal(cmds[i], sign))
		{
			if (cmds[i + 1])
			{
				if (f != NULL)
					free(f);
				f = ft_strdup((const char *)cmds[i + 1]);
			}
			else
			{
				if (f != NULL)
					free(f);
				f = NULL;
			}
		}
		i++;
	}
	return (f);
}

void	how_to_continue(t_data *data, char **cmds)
{
	int		i;
	int		flag;
	char	*file;

	i = -1;
	flag = 1;
	while (cmds[++i])
	{
		if (check_s_equal(cmds[i], ">") || check_s_equal(cmds[i], "<"))
		{
			flag = 2;
			file = get_file(cmds, cmds[i]);
			if (file && *file)
				check_redir(cmds, data, file, i);
			else
				printf("bash: syntax error near unexpected token `newline'\n");
			break ;
		}
	}
	if (flag == 1)
		exec_splitter(data, cmds);
}

void	init_args_to_heredoc(t_data *data, int i, char **cmds)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 6);
	if (!args)
	{
		perror("Memory allocation failed");
		data->exit_status = 1;
		return ;
	}
	args[0] = ft_strdup("echo");
	args[1] = ft_strdup(">");
	args[2] = ft_strdup("heredoc_skipper.txt");
	args[3] = ft_strdup((const char *)cmds[i]);
	args[4] = ft_strdup((const char *)cmds[i + 1]);
	args[5] = NULL;
	if (!args[0] || !args[1] || !args[2] || !args[3] || !args[4])
	{
		free_arr(args);
		data->exit_status = 1;
		return ;
	}
	exec_heredoc(data, args);
	free_arr(args);
}

void	free_exec_heredoc(char *key, char *file)
{
	if (file)
		free(file);
	if (key)
		free(key);
}

void	exec_append_skipper(t_data *data, char **cmds)
{
	int	i;
	int	j[2];
	int	fd;

	i = 0;
	j[0] = 0;
	j[1] = -1;
	while (cmds[j[0]])
	{
		if (check_s_equal(cmds[j[0]], ">>"))
			j[1] = j[0];
		j[0]++;
	}
	(void)data;
	while (cmds[i])
	{
		if (check_s_equal(cmds[i], ">>") && i != j[1])
		{
			fd = open(cmds[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			close(fd);
		}
		i++;
	}
}
