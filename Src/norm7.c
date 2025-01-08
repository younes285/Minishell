/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:27 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/01 20:09:46 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	g_s_helper(t_data *data)
{
	if (g_s == 2 || g_s == 3)
	{
		data->exit_status = 128 + g_s;
		g_s = 0;
	}
}

void	add_space_before_double_sp(t_data *data, int i, int *k, char *temp)
{
	temp[k[1]++] = ' ';
	temp[k[1]++] = data->cmds[i][k[0]++];
	temp[k[1]++] = data->cmds[i][k[0]];
	temp[k[1]++] = ' ';
}

void	ad_singel_helper2(t_data *data, int i, int *k, char *temp)
{
	if (data->cmds[i][k[0] + 2] != ' ')
	{
		temp[k[1]++] = data->cmds[i][k[0]++];
		temp[k[1]++] = data->cmds[i][k[0]];
		temp[k[1]++] = ' ';
	}
	else if (data->cmds[i][k[0] - 1] != ' ')
	{
		temp[k[1]++] = ' ';
		temp[k[1]++] = data->cmds[i][k[0]++];
		temp[k[1]++] = data->cmds[i][k[0]];
	}
}

void	ad_double_helper(t_data *data, int i, int *k, char *temp)
{
	temp[k[1]++] = ' ';
	temp[k[1]++] = data->cmds[i][k[0]];
	temp[k[1]++] = ' ';
}

void	ad_singel_helper(t_data *data, int i, int *k, char *temp)
{
	if (data->cmds[i][k[0] + 1] != ' ')
	{
		temp[k[1]++] = data->cmds[i][k[0]];
		temp[k[1]++] = ' ';
	}
	else if (data->cmds[i][k[0] - 1] != ' ')
	{
		temp[k[1]++] = ' ';
		temp[k[1]++] = data->cmds[i][k[0]];
	}
}
