/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:35:43 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 13:52:28 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static void	open_file2(const char *output, t_data *data)
{
	int	file;

	file = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

static	char	**prepare_args(int count, char **args
	, int *new_count, t_data *data)
{
	int		i[2];
	int		cmd_found;
	char	**new_args;

	if (init_redirect(i, &count, &cmd_found, &new_args) == 0)
		return (exit_error_2char(1, NULL, data));
	while (++i[0] < count)
	{
		if (ft_strcmp(args[i[0]], ">>") == 0)
			i[0]++;
		else
		{
			new_args[i[1]++] = ft_strdup((const char *)args[i[0]]);
			cmd_found = 1;
		}
	}
	new_args[i[1]] = NULL;
	if (cmd_found)
		*new_count = i[1];
	return (new_args);
}

void	append_continue(t_data *data, char **new_arg, char *file)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	open_file2(file, data);
	while (new_arg[++i])
	{
		if (check_s_equal(new_arg[i], "<<"))
		{
			exec_heredoc(data, new_arg);
			j = 1;
			break ;
		}
	}
	if (j != 1)
		how_to_continue(data, new_arg);
}

void	redirect_append(char **args, char *output, int count, t_data *data)
{
	int		pid;
	int		new_count;
	char	**new_args;

	new_args = prepare_args(count, args, &new_count, data);
	if (!new_args)
		return ;
	pid = fork();
	if (pid == -1)
	{
		free(new_args);
		return (exit_status_return(1, data));
	}
	if (pid == 0)
	{
		append_continue(data, new_args, output);
		free_redir(new_args, data, args, output);
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		free_arr(new_args);
	}
}
