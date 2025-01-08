/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:06:43 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 16:11:37 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec_out_skipper(t_data *data, char **cmds)
{
	int	i;
	int	j[2];
	int	fd;

	i = 0;
	j[0] = 0;
	j[1] = -1;
	while (cmds[j[0]])
	{
		if (check_s_equal(cmds[j[0]], ">"))
			j[1] = j[0];
		j[0]++;
	}
	(void)data;
	while (cmds[i])
	{
		if (check_s_equal(cmds[i], ">") && i != j[1])
		{
			fd = open(cmds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (exit_status_return(1, data));
			close(fd);
		}
		i++;
	}
}

char	**redirect_helper(int count, char **args, int *new_count, char *output)
{
	int		i[2];
	int		cmd_found;
	char	**new_args;

	if (init_redirect(i, &count, &cmd_found, &new_args) == 0)
		return (NULL);
	while (++i[0] < count)
	{
		if (ft_strcmp(args[i[0]], ">") == 0
			|| check_s_equal(args[i[0]], output) == 1)
			i[0]++;
		else
		{
			new_args[i[1]++] = ft_strdup((const char *)args[i[0]]);
			cmd_found = 1;
		}
	}
	new_args[i[1]] = NULL;
	*new_count = i[1];
	return (new_args);
}

void	cheld_red(t_data *data, char *output, char **new_args, char **args)
{
	open_file(output, data);
	how_to_continue(data, new_args);
	free_redir(NULL, data, args, output);
	exit(EXIT_SUCCESS);
}

void	redirect_output(char **args, char *output, int count, t_data *data)
{
	int		pid;
	int		new_count;
	char	**new_args;

	exec_out_skipper(data, args);
	new_args = redirect_helper(count, args, &new_count, output);
	if (!new_args)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		data->exit_status = 1;
		free(new_args);
		return ;
	}
	if (pid == 0)
		cheld_red(data, output, new_args, args);
	else
	{
		waitpid(pid, NULL, 0);
		data->exit_status = WEXITSTATUS(data->exit_status);
		free_redir_parent(NULL, new_args);
	}
}

int	is_operation(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
