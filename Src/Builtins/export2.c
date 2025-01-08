/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:47:23 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 17:06:28 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	update_or_add_env2(char **temp_env, int *j, char *arg)
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

char	**fill_env2(char **temp_env, int j, char **args, int count)
{
	int	i;

	if (args == NULL || count <= 0)
		return (temp_env);
	i = 1;
	while (i < count)
	{
		if (!update_or_add_env2(temp_env, &j, args[i]))
		{
			free_env(temp_env);
			return (NULL);
		}
		i++;
	}
	temp_env[j] = NULL;
	return (temp_env);
}

char	**free_return(char **new_env)
{
	free_env(new_env);
	return (NULL);
}

char	**export2(char **args, int count, char **new_env, t_data *data)
{
	char	**temp_env;
	int		i[2];
	int		l;

	if (new_env == NULL || new_env[0] == NULL || args == NULL || count <= 0)
		return (exit_error_2char(1, NULL, data));
	i[0] = 0;
	while (new_env[i[0]] != NULL)
		i[0]++;
	temp_env = malloc((i[0] + count + 1) * sizeof(char *));
	if (temp_env == NULL)
		free_return(new_env);
	i[1] = -1;
	while (++i[1] < i[0])
		temp_env[i[1]] = new_env[i[1]];
	temp_env = fill_env2(temp_env, i[1], args, count);
	if (temp_env == NULL)
	{
		free(new_env);
		return (NULL);
	}
	free(new_env);
	l = ft_strlen_2(temp_env);
	temp_env = bubble_sort(temp_env, l);
	return (temp_env);
}
