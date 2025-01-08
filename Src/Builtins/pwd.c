/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:15:16 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 16:52:25 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	pwd(int count, t_data *data)
{
	char	*pwd;

	count++;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (data->temp_pwd)
		{
			free(data->temp_pwd);
			data->temp_pwd = NULL;
		}
		data->temp_pwd = ft_strdup(pwd);
		printf("%s\n", data->temp_pwd);
		free(pwd);
		exit_status_return(0, data);
	}
	else
	{
		printf("%s\n", data->temp_pwd);
		data->exit_status = 1;
	}
}

void	path_helper2(t_data *data, char **updated_path)
{
	*updated_path = ft_strjoin(data->temp_pwd, "/..");
	if (*updated_path)
	{
		update_env(data, "PWD", *updated_path);
		if (data->temp_pwd)
		{
			free(data->temp_pwd);
			data->temp_pwd = NULL;
		}
		data->temp_pwd = ft_strdup(*updated_path);
		free(*updated_path);
	}
	printf("cd: error retrieving current directory: getcwd: ");
	printf("cannot access parent directories: No such file or directory\n");
}
