/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:47:23 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 17:07:41 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	update_or_add_env(char **temp_env, int *j, char *arg)
{
	int	k;

	if (!arg)
		return (0);
	k = 0;
	while (k < *j)
	{
		if (temp_env[k] && arg
			&& ft_strncmp(temp_env[k], arg, len(temp_env[k])) == 0)
		{
			free(temp_env[k]);
			temp_env[k] = ft_strdup(arg);
			if (temp_env[k] == NULL)
				return (0);
			return (1);
		}
		k++;
	}
	temp_env[*j] = ft_strdup(arg);
	if (temp_env[*j] == NULL)
		return (0);
	(*j)++;
	return (1);
}

char	**fill_env(char **temp_env, int *j, char **args, int count)
{
	int	i;

	i = 0;
	while (++i < count)
	{
		if (!is_valid_export_arg(args[i]))
			continue ;
		if (!update_or_add_env(temp_env, j, args[i]))
		{
			j[1] = 1;
			free_env(temp_env);
			return (NULL);
		}
	}
	temp_env[j[0]] = NULL;
	return (temp_env);
}

int	exp_arg_check(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&&!(str[0] >= 'A' && str[0] <= 'Z')
		&&str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!is_ok(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**check_export(char **new_env, t_data *data, char **args)
{
	int	k;

	k = 0;
	if (new_env == NULL)
		return (exit_error_2char(1, NULL, data));
	while (args[k])
	{
		if (args[k] && exp_arg_check(args[k]) == 0)
		{
			printf("not a valid identifier\n");
			data->exit_status = 1;
			return (new_env);
		}
		k++;
	}
	return (new_env);
}

char	**export(char **args, int count, char **new_env, t_data *data)
{
	char	**temp_env;
	int		i;
	int		j[2];

	new_env = check_export(new_env, data, args);
	i = 0;
	while (new_env[i] != NULL)
		i++;
	temp_env = malloc((i + count + 1) * sizeof(char *));
	if (temp_env == NULL)
	{
		free_env(new_env);
		return (exit_error_2char(1, NULL, data));
	}
	j[0] = 0;
	while (j[0] < i)
	{
		temp_env[j[0]] = new_env[j[0]];
		j[0]++;
	}
	temp_env = fill_env(temp_env, &j[0], args, count);
	free(new_env);
	return (temp_env);
}
