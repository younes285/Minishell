/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:27:29 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:33:30 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_path_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_path_command(char *path, char *command)
{
	char	*full_path;
	char	*temp;

	full_path = ft_strjoin(path, "/");
	if (full_path == NULL)
		return (NULL);
	temp = ft_strjoin(full_path, command);
	free(full_path);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

int	check_executable(char *command)
{
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0)
			return (0);
	}
	return (1);
}

char	*find_command_path(char *command, char **envp, t_data *data)
{
	char	**path_dirs;
	char	*path_env;
	char	*full_path;
	size_t	i;

	i = 0;
	if (check_executable(command) == 0)
		return (ft_strdup(command));
	path_env = get_path_env(envp);
	path_dirs = ft_split(path_env, ':');
	if (path_dirs == NULL)
		return (exit_error_char(1, NULL, data));
	while (path_dirs[i])
	{
		full_path = join_path_command(path_dirs[i], command);
		if (access(full_path, X_OK) == 0)
		{
			free_arr(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_arr(path_dirs);
	return (exit_error_char(1, NULL, data));
}
