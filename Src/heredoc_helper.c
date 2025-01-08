/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:58:52 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/01 17:17:23 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	init_heredoc_helper(char ***new_args, int *i, int *j, int count)
{
	(*new_args) = malloc(sizeof(char *) * (count + 3));
	if (!(*new_args))
	{
		return ;
	}
	*i = -1;
	*j = 0;
}

void	heredoc_cmd_found(char ***new_args, int *j, int *i, int *cmd_found)
{
	(*new_args)[(*j)++] = ft_strdup("<");
	(*new_args)[(*j)++] = ft_strdup("heredoc_output.txt");
	if (!(*new_args)[(*j) - 2] || !(*new_args)[(*j) - 1])
	{
		free_arr((*new_args));
		return ;
	}
	*cmd_found = 1;
	(*i)++;
}

void	exit_status_exit(int status, int for_exit, t_data *data)
{
	data->exit_status = status;
	exit(for_exit);
}

int	is_quoted(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (1);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	return (0);
}
