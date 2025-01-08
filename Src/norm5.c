/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:01:05 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/01 20:02:23 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec_child_process(t_data *data, char **args)
{
	restore_signals();
	exec_cmd(data, args);
	exit(0);
}

void	handle_command_not_found(char **args, t_data *data)
{
	(void) args;
	(void) data;
	ft_putendl_fd("command not found", 2);
	exit(127);
}

void	is_directory(char *cmd_path, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		printf("is a directory\n");
		free(cmd_path);
		data->exit_status = 126;
		exit(EXIT_FAILURE);
	}
}

char	*trim_whitespace(char *str)
{
	char		*end;
	size_t		len;
	char		*trimmed;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 0)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;
	len = end - str + 1;
	trimmed = malloc(len + 1);
	if (trimmed)
	{
		ft_strncpy(trimmed, str, len);
		trimmed[len] = '\0';
	}
	return (trimmed);
}
