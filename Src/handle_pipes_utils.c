/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:21:49 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:33:45 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	where_to_go(t_data *data, char *cmd)
{
	if (ft_strstr(cmd, "<<") || ft_strstr(cmd, ">>"))
		exec_heredoc_helper(data, cmd);
	else if (ft_strchr((const char *)cmd, '<')
		|| ft_strchr((const char *)cmd, '>'))
		exec_redir(data, cmd);
}

void	exec_helper_pipes(t_data *data, char **args, int save_std[2])
{
	char	*cmd_path;

	cmd_path = find_command_path(args[0], data->env, data);
	if (cmd_path == NULL)
	{
		dup2(save_std[1], STDOUT_FILENO);
		free_arr(args);
		free_data(data);
		ft_putendl_fd("command not found", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, data->env) == -1)
	{
		perror("execve");
		free_arr(args);
		free(cmd_path);
		free_data(data);
		exit(EXIT_FAILURE);
	}	
}

void	child_process(int i, int **pipes, char **cmds)
{
	if (i != 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i != ft_strlen_2(cmds) - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	if (i != 0)
	{
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
	}
	if (i != ft_strlen_2(cmds) - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	parent_process(int i, int **pipes, char **cmds, char **args)
{
	if (i != 0)
		close(pipes[i - 1][0]);
	if (i != ft_strlen_2(cmds) - 1)
		close(pipes[i][1]);
	if (args)
		free_arr(args);
}
