/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:09:35 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 11:14:28 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	process_command(char *command, t_data *data, int i)
{
	free(data->cmds[i]);
	data->cmds[i] = delete_spaces(command, data);
	return (1);
}

void	process_input(char *input, t_data *data)
{
	char	**commands;
	int		i;

	commands = ft_split_2(input, ';');
	free(input);
	if (!commands)
	{
		ft_putendl_fd("Error splitting commands", 2);
		data->exit_status = 1;
		return ;
	}
	i = -1;
	init_data_cmds(commands, data);
	while (i++, commands[i])
	{
		if (process_command(commands[i], data, i) == 0)
		{
			free_arr(commands);
			exit(1);
		}
	}
	data->cmds[i] = NULL;
	free_arr(commands);
}
