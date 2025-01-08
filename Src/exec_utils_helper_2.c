/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:28:48 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 11:45:34 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	add_double_sp_doc(t_data *data, int i, int *j)
{
	char	*temp;
	int		k[2];

	k[0] = -1;
	k[1] = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 3));
	free_and_return(temp, data);
	while (k[0]++, data->cmds[i][k[0]])
	{
		if (k[0] != *j)
			temp[k[1]++] = data->cmds[i][k[0]];
		else
		{
			temp[k[1]++] = ' ';
			temp[k[1]++] = data->cmds[i][k[0]++];
			temp[k[1]++] = data->cmds[i][k[0]];
			temp[k[1]++] = ' ';
		}
	}
	temp[k[1]] = '\0';
	free(data->cmds[i]);
	data->cmds[i] = ft_strdup((const char *)temp);
	free(temp);
	*j += 2;
}

void	add_single_sp_doc(t_data *data, int i, int *j)
{
	char	*temp;
	int		k[2];

	k[0] = -1;
	k[1] = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 2));
	if (!temp)
	{
		free_data(data);
		return ;
	}
	while (k[0]++, data->cmds[i][k[0]])
	{
		if (k[0] != *j && k[0] != *j + 1)
			temp[k[1]++] = data->cmds[i][k[0]];
		else
			ad_singel_helper2(data, i, k, temp);
	}
	temp[k[1]] = '\0';
	free(data->cmds[i]);
	data->cmds[i] = ft_strdup((const char *)temp);
	free(temp);
	*j += 2;
}

void	add_double_sp(t_data *data, int i, int j)
{
	char	*temp;
	int		k[2];

	k[0] = -1;
	k[1] = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 3));
	if (!temp)
	{
		free_data(data);
		return ;
	}
	while (k[0]++, data->cmds[i][k[0]])
	{
		if (k[0] != j)
			temp[k[1]++] = data->cmds[i][k[0]];
		else
			ad_double_helper(data, i, k, temp);
	}
	temp[k[1]] = '\0';
	free(data->cmds[i]);
	data->cmds[i] = ft_strdup((const char *)temp);
	free(temp);
}

void	add_single_sp(t_data *data, int i, int j)
{
	char	*temp;
	int		k[2];

	k[0] = -1;
	k[1] = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 2));
	if (!temp)
	{
		free_data(data);
		return ;
	}
	while (k[0]++, data->cmds[i][k[0]])
	{
		if (k[0] != j)
			temp[k[1]++] = data->cmds[i][k[0]];
		else
			ad_singel_helper(data, i, k, temp);
	}
	temp[k[1]] = '\0';
	free(data->cmds[i]);
	data->cmds[i] = ft_strdup((const char *)temp);
	free(temp);
}

void	add_necessary_sp(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmds[i][j])
	{
		if (data->cmds[i][j + 1] && ((data->cmds[i][j] == '>'
			&& data->cmds[i][j + 1] == '>')
			|| (data->cmds[i][j] == '<' && data->cmds[i][j + 1] == '<')))
			add_necessary_helper(data, i, j);
		else if (data->cmds[i][j] == '|' || (data->cmds[i][j] == '>'
		&& data->cmds[i][j + 1] != '>' && j > 0 && data->cmds[i][j - 1] != '>')
		|| (j > 0 && data->cmds[i][j] == '<' && data->cmds[i][j + 1] != '<'
		&& data->cmds[i][j - 1] != '<'))
		{
			if (data->cmds[i][j - 1] != ' '
				&& data->cmds[i][j + 1] != ' ')
				add_double_sp(data, i, j);
			else if ((data->cmds[i][j - 1] != ' ')
				|| data->cmds[i][j + 1] != ' ')
				add_single_sp(data, i, j);
		}
		j++;
	}
}
