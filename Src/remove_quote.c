/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:14:47 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/03 17:45:01 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	remove_ttq_helper(char *temp, char **cmd, int i[3])
{
	if (temp[i[1]] != '\0' && temp[i[1]] != '\'' && temp[i[1]] != '\"')
	{
		(*cmd)[i[2]] = temp[i[1]];
		i[1]++;
		i[2]++;
	}
}

void	remove_ttq_s(char *temp, char **cmd, int i[3])
{
	char	c;

	c = temp[i[1]];
	i[1]++;
	while (temp[i[1]] && temp[i[1]] != c)
	{
		(*cmd)[i[2]] = temp[i[1]];
		i[1]++;
		i[2]++;
	}
	i[1]++;
}

void	exit_remove(t_data *data, char **args, char *temp)
{
	data->exit_status = 1;
	free_arr(args);
	free_data(data);
	free(temp);
	exit(1);
}

void	remove_quote(t_data *data, char **args)
{
	char	*temp;
	int		i[3];

	i[0] = -1;
	while (args[++i[0]])
	{
		temp = ft_strdup((const char *)args[i[0]]);
		free(args[i[0]]);
		args[i[0]] = (char *)malloc(sizeof(char)
				* (ft_strlen((const char *)temp) + 1));
		if (!args[i[0]])
			exit_remove(data, args, temp);
		i[1] = 0;
		i[2] = 0;
		while (temp[i[1]])
		{
			if (temp[i[1]] == '\'' || temp[i[1]] == '\"')
				remove_ttq_s(temp, &args[i[0]], i);
			remove_ttq_helper(temp, &args[i[0]], i);
		}
		args[i[0]][i[2]] = '\0';
		free(temp);
	}
}
