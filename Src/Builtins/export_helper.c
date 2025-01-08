/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:28 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 16:34:42 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_env(char **env)
{
	int	i;

	if (env == NULL)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	is_valid_export_arg(char *arg)
{
	char	*equals_sign;

	if (!arg)
		return (0);
	equals_sign = ft_strchr(arg, '=');
	if (equals_sign == NULL)
		return (0);
	if (ft_strchr(equals_sign + 1, '=') != NULL)
		return (0);
	if (equals_sign == arg)
		return (0);
	return (1);
}

int	len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
