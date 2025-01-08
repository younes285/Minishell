/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:18:46 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:32:45 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	exit_error_int(int exit_status, int returned, t_data *data)
{
	data->exit_status = exit_status;
	return (returned);
}

void	exit_status_helper(char *str, int i, t_data *data)
{
	perror(str);
	data->exit_status = i;
}

void	exit_status_return(int i, t_data *data)
{
	data->exit_status = i;
	return ;
}

char	*exit_error_char(int exit_status, char *returned, t_data *data)
{
	data->exit_status = exit_status;
	return (returned);
}

char	**exit_error_2char(int exit_status, char **returned, t_data *data)
{
	data->exit_status = exit_status;
	return (returned);
}
