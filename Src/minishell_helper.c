/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:47:49 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 16:03:12 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_strlen_2(char **c)
{
	int	i;

	i = 0;
	while (c[i] != NULL)
		i++;
	return (i);
}

void	init_data_helper(t_data **data, char **env)
{
	int	i;
	int	l;

	l = ft_strlen_2(env);
	(*data)->env = (char **)malloc(sizeof(char *) * (l + 1));
	if (!((*data)->env))
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		free_arr((*data)->history);
		free(*data);
		exit_status_exit(1, 1, *data);
	}
	i = 0;
	while (i < l)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		if (!((*data)->env[i]))
		{
			ft_putendl_fd("Error: Memory allocation failed", 2);
			free_data(*data);
			exit_status_exit(1, 1, *data);
		}
		i++;
	}
	(*data)->env[l] = NULL;
}

void	init_data_helper2(t_data **data, char **env)
{
	int		i;
	int		l;

	l = ft_strlen_2(env);
	(*data)->env2 = (char **)malloc(sizeof(char *) * (l + 1));
	if (!((*data)->env2))
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		free_arr((*data)->history);
		free(*data);
		exit_status_exit(1, 1, *data);
	}
	i = -1;
	while (++i < l)
	{
		(*data)->env2[i] = ft_strdup(env[i]);
		if (!((*data)->env2[i]))
		{
			ft_putendl_fd("Error: Memory allocation failed", 2);
			free_data(*data);
			exit_status_exit(1, 1, *data);
		}
	}
	(*data)->env2[l] = NULL;
	(*data)->env2 = bubble_sort((*data)->env2, l);
}

int	check_trim(char *input)
{
	char	*trim;

	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	trim = ft_strtrim(input, " \t\f");
	if (trim[0] == '\0')
	{
		free(input);
		free(trim);
		return (0);
	}
	free(trim);
	return (1);
}

void	init_help(t_data **data, char **env)
{
	char	*temp;

	temp = get_path("SHLVL", env, (*data));
	(*data)->shlvl = ft_atoi(temp);
	(*data)->temp_pwd = NULL;
	free(temp);
}
