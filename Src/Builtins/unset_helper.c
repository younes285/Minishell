/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:11:50 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 15:29:15 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	count_env_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**create_new_env(int count, t_data *data)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (exit_error_2char(1, NULL, data));
	return (new_env);
}

int	copy_env_var(char **new_env, char *env_var, int index)
{
	new_env[index] = ft_strdup(env_var);
	if (!new_env[index])
		return (0);
	return (1);
}
