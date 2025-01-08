/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:46:31 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 16:47:48 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	path_exist(char *target, char *current, char **previous, t_data *data)
{
	char	*new_pwd;
	char	*t;

	t = get_path("PWD", data->env, data);
	if (!t)
		update_env(data, "OLDPWD", "");
	free(t);
	if (chdir(target) != 0)
		exit_status_helper("cd", 1, data);
	else
	{
		data->exit_status = 0;
		if (*previous)
			free(*previous);
		if (current)
			*previous = ft_strdup((const char *)current);
		else
			*previous = NULL;
		t = get_path("PWD", data->env, data);
		if (current && t)
			update_env(data, "OLDPWD", current);
		free(t);
		new_pwd = getcwd(NULL, 0);
		path_exist_helper(data, new_pwd, target);
	}
}

void	old_exist(t_data *data, char *oldpwd, char *current, char **previous)
{
	if (!*previous)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	printf("%s\n", oldpwd);
	path_exist(*previous, current, previous, data);
}

void	cd_helper(t_data *data, char **args, char *current, char **previous)
{
	char	*target;
	char	*oldpwd;

	target = ft_strdup((const char *)args[1]);
	if (ft_strncmp(target, "-", 2) == 0)
	{
		oldpwd = get_path("OLDPWD", data->env, data);
		if (oldpwd && ft_strlen(oldpwd) > 0)
		{
			if (chdir(oldpwd) != 0)
				exit_status_helper("cd", 1, data);
			else
			{
				old_exist(data, oldpwd, current, previous);
				data->exit_status = 0;
			}
		}
		else
			exit_error_print(1, "cd: OLDPWD not set or empty\n", data);
		free(oldpwd);
	}
	else
		path_exist(target, current, previous, data);
	free(target);
}

void	home_case(t_data *data, char *current, char **previous)
{
	char	*home;

	home = get_path("HOME", data->env, data);
	if (home)
	{
		if (chdir(home) != 0)
			exit_status_helper("cd", 1, data);
		else
		{
			change(data, home, current);
			if (*previous)
				free(*previous);
			*previous = ft_strdup((const char *)current);
			data->exit_status = 0;
		}
		free(home);
	}
	else
		printf("cd: HOME not set\n");
}

void	cd(char *args[], int count, t_data *data, char **previous)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
		data->exit_status = 1;
	if (count == 0)
		home_case(data, data->temp_pwd, previous);
	else if (count == 1)
	{
		if (ft_strcmp(args[1], "~") == 0)
			home_case(data, current, previous);
		else if (ft_strncmp(args[1], "~/", 2) == 0)
			home2_case(args, data, current, previous);
		else
			cd_helper(data, args, current, previous);
	}
	else
	{
		printf("cd: too many arguments\n");
		data->exit_status = 1;
	}
	if (current)
		free(current);
}
