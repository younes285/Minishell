/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:55:54 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/30 19:37:51 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	only_n(char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_helper(char **arg, int i, int count, t_data *data)
{
	while (i < count)
	{
		if (printf("%s", arg[i]) < 0)
		{
			exit_status_helper("echo: printf error", 1, data);
			return ;
		}
		if (i < count - 1)
		{
			if (printf(" ") < 0)
			{
				exit_status_helper("echo: printf error", 1, data);
				return ;
			}
		}
		i++;
	}
}

void	echo(char **arg, int count, t_data *data)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (count > 1 && ft_strncmp(arg[1], "-n", 2) == 0)
	{
		while (i < count && ft_strncmp(arg[i], "-n", 2) == 0
			&& only_n(arg[i]) == 1)
		{
			new_line = 0;
			i++;
		}
	}
	echo_helper(arg, i, count, data);
	if (new_line)
	{
		if (printf("\n") < 0)
		{
			exit_status_helper("echo: printf error", 1, data);
			return ;
		}
	}
	data->exit_status = 0;
}
