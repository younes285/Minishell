/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:05:22 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 13:32:46 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	init_redirect(int i[2], int *count, int *cmd_found, char ***new_args)
{
	*new_args = (char **)malloc(sizeof(char *) * (*count + 1));
	if (!*new_args)
	{
		return (0);
	}
	i[0] = -1;
	i[1] = 0;
	*cmd_found = 0;
	return (1);
}

char	**redir_helper(int count, char **args, int *new_count, char *output)
{
	int		i[2];
	int		cmd_found;
	char	**new_args;

	if (init_redirect(i, &count, &cmd_found, &new_args) == 0)
		return (NULL);
	while (++i[0] < count)
	{
		if ((ft_strcmp(args[i[0]], "<") == 0
				|| check_s_equal(args[i[0]], output) == 1))
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

void	free_redir_parent(char **args, char **new_args)
{
	free_arr(args);
	free_arr(new_args);
}

void	redin_child(t_data *data, char **args, char *file, char **new_args)
{
	open_input_file(file, data);
	how_to_continue(data, new_args);
	free_redir(NULL, data, args, file);
	exit(EXIT_SUCCESS);
}

void	redirect_input(char **args, char *input_file, int count, t_data *data)
{
	int		pid;
	int		new_count;
	char	**new_args;
	int		status;

	new_args = redir_helper(count, args, &new_count, input_file);
	if (!new_args)
		return ;
	pid = fork();
	if (pid == -1)
	{
		free_arr(new_args);
		return (exit_status_return(1, data));
	}
	if (pid == 0)
		redin_child(data, args, input_file, new_args);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		free_redir_parent(NULL, new_args);
	}
}
