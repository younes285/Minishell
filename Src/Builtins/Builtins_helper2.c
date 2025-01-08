/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtins_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:58:36 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 16:45:10 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	update_env(t_data *data, char *key, char *value)
{
	char	*t;

	t = get_path(key, data->env, data);
	if (!key || !value)
		return ;
	if (t)
		my_set_env(&data->env, key, value, data);
	free(t);
	t = get_path(key, data->env2, data);
	if (t)
		my_set_env(&data->env2, key, value, data);
	free(t);
}

void	path_exist_helper(t_data *data, char *new_pwd, char *target)
{
	char	*updated_path;

	if (new_pwd)
	{
		update_env(data, "PWD", new_pwd);
		if (data->temp_pwd)
		{
			free(data->temp_pwd);
			data->temp_pwd = NULL;
		}
		data->temp_pwd = getcwd(NULL, 0);
		free(new_pwd);
	}
	else if (ft_strcmp(target, "..") == 0)
		path_helper2(data, &updated_path);
	else
	{
		printf("cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
	}
}

void	exit_error_print(int exit_status, char *str, t_data *data)
{
	data->exit_status = exit_status;
	printf("%s", str);
}

void	home2_case(char **args, t_data *data, char	*current, char **previous)
{
	char	*home_dir;
	char	*rest_of_path;
	char	*full_path;

	home_dir = get_path("HOME", data->env, data);
	if (home_dir)
	{
		rest_of_path = args[1] + 2;
		full_path = ft_strjoin(home_dir, "/");
		full_path = ft_strjoin(full_path, rest_of_path);
		printf("%s\n", full_path);
		free(home_dir);
		path_exist(full_path, current, previous, data);
		free(full_path);
	}
	else
	{
		printf("cd: HOME not set\n");
		data->exit_status = 1;
	}
}

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	if (arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (0);
	if (ft_strcmp(arg, "9223372036854775808") == 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
