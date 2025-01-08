/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:50:26 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 17:24:36 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	unset_helper2(char **new_env, char **env, int *i, int j)
{
	if (!copy_env_var(new_env, env[j], *i))
	{
		while (*i > 0)
			free(new_env[--(*i)]);
		free(new_env);
		return ;
	}
	else
		(*i)++;
}

void	unset_helper1(char **args, char **env, char **new_env, int count)
{
	int	i;
	int	j;
	int	k;
	int	remove;

	i = 0;
	j = 0;
	while (env[j])
	{
		remove = 0;
		k = 0;
		while (++k < count)
		{
			if (ft_strncmp(env[j], args[k], ft_strlen(args[k])) == 0
				&& env[j][ft_strlen(args[k])] == '=')
			{
				remove = 1;
				break ;
			}
		}
		if (!remove)
			unset_helper2(new_env, env, &i, j);
		j++;
	}
	new_env[i] = NULL;
}

char	**unset_free(int i, char **env, char **new_env)
{
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

char	**unset(char **args, int count, char **env, t_data *data)
{
	char	**new_env;
	int		i;
	int		k;

	k = 1;
	i = count_env_vars(env);
	new_env = create_new_env(i, data);
	if (!new_env)
	{
		free_env(env);
		return (exit_error_2char(1, NULL, data));
	}
	while (k <= count)
	{
		if (args[k] && exp_arg_check2(args[k]) == 0)
		{
			printf("not a valid identifier\n");
			data->exit_status = 1;
			return (env);
		}
		k++;
	}
	unset_helper1(args, env, new_env, count);
	new_env = unset_free(i, env, new_env);
	return (new_env);
}

char	**unset2(char **args, int count, char **env, t_data *data)
{
	char	**new_env;
	int		i;
	int		k;

	k = 1;
	i = count_env_vars(env);
	new_env = create_new_env(i, data);
	if (!new_env)
	{
		free_env(env);
		return (exit_error_2char(1, NULL, data));
	}
	while (k <= count)
	{
		if (args[k] && exp_arg_check(args[k]) == 0)
		{
			data->exit_status = 1;
			return (env);
		}
		k++;
	}
	unset_helper1(args, env, new_env, count);
	new_env = unset_free(i, env, new_env);
	return (new_env);
}
