/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:51:50 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/04 11:32:53 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	count_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static void	perror_exit(t_data *data)
{
	perror("malloc");
	data->exit_status = 1;
	exit(EXIT_FAILURE);
}

char	**return_env(char **env, t_data *data)
{
	char	**result;
	int		i;
	int		num_vars;

	num_vars = count_vars(env);
	result = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (result == NULL)
		perror_exit(data);
	i = 0;
	while (i < num_vars)
	{
		result[i] = ft_strdup(env[i]);
		if (result[i] == NULL)
		{
			perror("strdup");
			while (i > 0)
				free (result[--i]);
			free(result);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	result[num_vars] = NULL;
	return (result);
}

void	env(char **envp, t_data *data)
{
	char	**copied_env;
	int		i;

	i = 0;
	copied_env = return_env(envp, data);
	if (!copied_env)
	{
		data->exit_status = 1;
		return ;
	}
	while (copied_env[i])
	{
		printf("%s\n", copied_env[i]);
		free(copied_env[i]);
		i++;
	}
	free(copied_env);
	data->exit_status = 0;
}

void	env2(char **envp, t_data *data)
{
	char	**copied_env;
	int		i;
	int		j;

	i = 0;
	copied_env = return_env(envp, data);
	if (!copied_env)
		return (exit_status_return(1, data));
	while (copied_env[i])
	{
		j = 0;
		j = env_helper(copied_env, i, j, data);
		printf("=\"");
		while (j < (int)ft_strlen(copied_env[i]) - 1 && copied_env[i][j])
		{
			printf ("%c", copied_env[i][j]);
			j++;
		}
		printf("\"\n");
		free(copied_env[i]);
		i++;
	}
	free(copied_env);
	data->exit_status = 0;
}
