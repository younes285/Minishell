/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:29:02 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 14:14:13 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	here_pipe_heper(t_her_data *data_her, char **cmds)
{
	her_pipe_process(data_her);
	close(data_her->fd);
	data_her->cmd_tmp = ft_strdup((const char *)cmds[data_her->i]);
	free(cmds[data_her->i]);
	cmds[data_her->i] = ft_strreplace(data_her->cmd_tmp, "<<", "<");
	free(data_her->cmd_tmp);
	data_her->cmd_tmp = ft_strdup((const char *)cmds[data_her->i]);
	free(cmds[data_her->i]);
	cmds[data_her->i] = ft_strreplace(data_her->cmd_tmp,
			data_her->key, data_her->temp_file);
	free(data_her->key);
	free(data_her->cmd_tmp);
	free(data_her->temp_file);
}

void	handle_heredoc_helper2(t_her_data *data_her, char **new_cmds
	, char **cmds)
{
	int	y;

	y = 0;
	while (new_cmds[y])
	{
		data_her->temp_file = NULL;
		if (ft_strstr(cmds[data_her->i], "<<"))
		{
			data_her->key = get_key(cmds[data_her->i]);
			if (!data_her->key)
			{
				printf("Error: Missing delimiter for heredoc\n");
				return ;
			}
			if (!data_her->temp_file)
				data_her->temp_file = ft_strdup(data_her->key);
			data_her->fd = open(data_her->temp_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			here_pipe_heper(data_her, cmds);
		}
		y++;
	}
}

void	handle_heredoc(char **cmds)
{
	t_her_data	data_her;
	char		**new_cmds;

	data_her.i = 0;
	while (cmds[data_her.i])
	{
		if (ft_strstr(cmds[data_her.i], ">"))
			her_help(&data_her, cmds);
		new_cmds = ft_split_2(cmds[data_her.i], ' ');
		handle_heredoc_helper2(&data_her, new_cmds, cmds);
		free_arr(new_cmds);
		data_her.i++;
	}
}

void	handle_pipes_helper(t_pipe *s_pipe, int count, char **cmds
	, t_data *data)
{
	restore_signals();
	setup_child_pipes(s_pipe->i, count, s_pipe->pipes);
	close_unused_pipes(s_pipe->i, count, s_pipe->pipes);
	execute_command(data, cmds[s_pipe->i], s_pipe->save_std);
	free_arr(cmds);
	exit(EXIT_SUCCESS);
}

void	handle_pipes(t_data *data, char **cmds, int count)
{
	t_pipe	s_pipe;

	s_pipe.pipes = malloc(sizeof(int *) * (count - 1));
	s_pipe.pids = malloc(sizeof(pid_t) * count);
	handle_heredoc(cmds);
	create_pipes(count, &s_pipe.pipes, data);
	s_pipe.i = -1;
	save_std_fds(&s_pipe.save_std[0], &s_pipe.save_std[1]);
	while (++s_pipe.i < count)
	{
		s_pipe.pids[s_pipe.i] = fork();
		if (s_pipe.pids[s_pipe.i] == -1)
			my_exit_helper("Fork failed", data);
		else if (s_pipe.pids[s_pipe.i] == 0)
			handle_pipes_helper(&s_pipe, count, cmds, data);
		else
			ignore_signals();
	}
	free_arr(cmds);
	close_pipes(s_pipe.pipes, count);
	while (s_pipe.i--)
		waitpid(s_pipe.pids[s_pipe.i], NULL, 0);
	free(s_pipe.pids);
}
