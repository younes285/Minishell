/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:04:22 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/04 12:18:47 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exit_check(t_data *data, char **args)
{
	int	exit_s;

	if (is_numeric(args[1]) == 0)
	{
		printf("exit\nexit: %s : numeric argument required\n", args[1]);
		data->exit_status = 255;
		exit_s = 255;
		free_helper(args, data);
		exit(exit_s);
	}
	else
	{
		data->exit_status = ft_atoi(args[1]);
		if (data->exit_status < 0 || data->exit_status > 255)
			data->exit_status = 255;
		printf("exit\n");
		exit_s = data->exit_status;
		free_helper(args, data);
		exit(exit_s);
	}
}

void	exit2_check(t_data *data, char **args)
{
	if (is_numeric(args[1]) == 0)
	{
		printf("exit\nexit: %s : numeric argument required\n", args[1]);
		data->exit_status = 255;
		free_helper(args, data);
		exit(255);
	}
	else
	{
		data->exit_status = ft_atoi(args[1]);
		if (data->exit_status < 0 || data->exit_status > 255)
			data->exit_status = 255;
		free_helper(args, data);
		exit(data->exit_status);
	}
}

void	exit_check2(t_data *data, char **args)
{
	if (is_numeric(args[1]) == 0)
	{
		printf("exit\nexit: %s : numeric argument required\n", args[1]);
		data->exit_status = 255;
		free_helper(args, data);
		exit(255);
	}
	else
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
	}
}

void	my_exit(char **args, t_data *data)
{
	int		count;

	count = 0;
	while (args[count] != NULL)
		count++;
	if (count == 1)
	{
		printf("exit\n");
		free_helper(args, data);
		exit(0);
	}
	else if (count == 2)
		exit_check(data, args);
	else
		exit_check2(data, args);
}

void	my_exit2(char **args, t_data *data)
{
	int		count;

	count = 0;
	while (args[count] != NULL)
		count++;
	if (count == 1)
	{
		free_helper(args, data);
		exit(0);
	}
	else if (count == 2)
		exit2_check(data, args);
	else
		exit_check2(data, args);
}
