/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:02:35 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 16:13:57 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	open_file(char *output, t_data *data)
{
	int	file;

	file = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror("open");
		data->exit_status = 1;
		return ;
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(file);
		data->exit_status = 1;
		return ;
	}
	close(file);
}

void	exec_cmd_free(char **args, t_data *data)
{
	free_arr(args);
	free_data(data);
	data->exit_status = 0;
}

void	ft_strdup_2(t_data *data, char **to_dup)
{
	int	i;

	free_arr(data->cmds);
	i = 0;
	data->cmds = (char **)malloc(sizeof(char *) * (ft_strlen_2(to_dup) + 1));
	data->cmds[ft_strlen_2(to_dup)] = NULL;
	while (to_dup[i])
	{
		data->cmds[i] = to_dup[i];
		free(to_dup[i]);
		i++;
	}
	free(to_dup);
}

void	free_redir(char **new_args, t_data *data, char **args, char *output)
{
	free_arr(new_args);
	free_data(data);
	free_arr(args);
	free(output);
	rl_clear_history();
}

void	check_redir(char **cmds, t_data *data, char *file, int i)
{
	if (check_s_equal(cmds[i], ">"))
		redirect_output(cmds, file, ft_strlen_2(cmds), data);
	else
		redirect_input(cmds, file, ft_strlen_2(cmds), data);
	free(file);
}
