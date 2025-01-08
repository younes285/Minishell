/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:29:02 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/01 14:28:27 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	create_pipes(int count, int ***pipes, t_data *data)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i] || pipe((*pipes)[i]) == -1)
		{
			close_pipes(*pipes, i);
			my_exit_helper("Parent: pipe creation failed", data);
		}
		i++;
	}
}

void	setup_child_pipes(int i, int cmd_count, int **pipes)
{
	if (i != 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	if (i != cmd_count - 1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
}

void	close_unused_pipes(int i, int cmd_count, int **pipes)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

char	*get_key(char *s)
{
	int		i[2];
	char	*key;

	i[0] = 0;
	i[1] = 1;
	while (s[i[0]])
	{
		if (s[i[0]] == '<' && s[i[0] + 1] == '<')
		{
			i[0] += 2;
			while (s[i[0]] && s[i[0]] == ' ')
				i[0]++;
			i[1] = i[0];
			while (s[i[0]] && s[i[0]] != ' ' && s[i[0]] != '\0')
				i[0]++;
			key = malloc(i[0] - i[1] + 1);
			if (!key)
				return (NULL);
			ft_strncpy(key, s + i[1], i[0] - i[1]);
			key[i[0] - i[1]] = '\0';
			return (key);
		}
		i[0]++;
	}
	return (NULL);
}
