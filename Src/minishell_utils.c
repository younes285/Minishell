/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:13:45 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/03 17:22:04 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_arr(char **input)
{
	int	i;

	if (!input)
		return ;
	i = 0;
	while (input[i])
	{
		if (input[i])
			free(input[i]);
		i++;
	}
	free(input);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmds)
		free_arr(data->cmds);
	if (data->env)
		free_arr(data->env);
	if (data->env2)
		free_arr(data->env2);
	if (data->history)
		free_arr(data->history);
	if (data->previous)
		free(data->previous);
	if (data->temp_pwd)
	{
		free(data->temp_pwd);
		data->temp_pwd = NULL;
	}
	free(data);
}

void	free_data_2(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		free_arr(data->env);
	if (data->env2)
		free_arr(data->env2);
	if (data->history)
		free_arr(data->history);
	if (data->previous)
		free(data->previous);
	if (data->temp_pwd)
	{
		free(data->temp_pwd);
		data->temp_pwd = NULL;
	}
	free(data);
}

int	handle_quote(char *input, char **ret, int i[3], char quote)
{
	(*ret)[i[1]++] = input[i[0]++];
	while (input[i[0]] != quote && input[i[0]])
	{
		(*ret)[i[1]] = input[i[0]];
		i[0]++;
		i[1]++;
	}
	if (!input[i[0]])
	{
		free(*ret);
		ft_putendl_fd("Error: Unclosed quote", 2);
		return (0);
	}
	(*ret)[i[1]] = input[i[0]];
	i[0]++;
	i[1]++;
	return (1);
}

void	handle_spaces(char *input, char **ret, int i[3])
{
	if ((input[i[0]] == ' ' && input[i[0] + 1] == ' ')
		|| (input[i[0]] == '\t' && input[i[0] + 1] == '\t'))
		i[0]++;
	else
	{
		(*ret)[i[1]] = input[i[0]];
		i[0]++;
		i[1]++;
	}
}
