/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:44:45 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:33:38 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_and_exit_pipe(char **cmds, char **args, int **pipes, t_data *data)
{
	free_arr(cmds);
	if (args)
		free_arr(args);
	(void)pipes;
	free_data(data);
	exit(1);
}

void	exec_pipe_redir(char **cmds, t_data *data, int **pipes, int i)
{
	pid_t	pid1;
	int		status;

	pid1 = fork();
	if (pid1 == -1)
	{
		free_data(data);
		exit(1);
	}
	if (pid1 == 0)
	{
		child_process(i, pipes, cmds);
		exec_redir(data, cmds[i]);
		free_and_exit_pipe(cmds, NULL, pipes, data);
	}
	parent_process(i, pipes, cmds, NULL);
	waitpid(pid1, &status, 0);
}
