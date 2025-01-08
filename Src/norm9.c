/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:00:28 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 14:05:52 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	open_test(int f)
{
	if (f == -1)
		perror("Error opening input file");
}

void	handle_redirections(char *cmd, int *input_fd, int *o_f)
{
	char	**parts;
	int		i;

	parts = ft_split(cmd, ' ');
	i = 0;
	while (parts[i])
	{
		if (ft_strcmp(parts[i], "<") == 0 && parts[i + 1])
		{
			*input_fd = open(parts[i + 1], O_RDONLY);
			open_test(*input_fd);
		}
		else if (ft_strcmp(parts[i], ">") == 0 && parts[i + 1])
		{
			*o_f = open(parts[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			open_test(*o_f);
		}
		else if (ft_strcmp(parts[i], ">>") == 0 && parts[i + 1])
		{
			*o_f = open(parts[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			open_test(*input_fd);
		}
		i++;
	}
	free_arr(parts);
}

void	remove_redirections_helper(char ***parts, int *len, int *i, char *cmd)
{
	*parts = ft_split_2(cmd, ' ');
	*i = 0;
	*len = 0;
	while ((*parts)[*i])
	{
		if (ft_strcmp((*parts)[*i], "<") != 0
			&& ft_strcmp((*parts)[*i], ">") != 0
			&& ft_strcmp((*parts)[*i], ">>") != 0
			&& (*i == 0 || (ft_strcmp((*parts)[*i - 1], "<") != 0
					&& ft_strcmp((*parts)[*i - 1], ">") != 0
					&& ft_strcmp((*parts)[*i - 1], ">>") != 0)))
			*len += ft_strlen((*parts)[*i]) + 1;
		(*i)++;
	}
}

char	*remove_redirections(char *cmd)
{
	char	**parts;
	char	*result;
	int		i;
	int		len;

	remove_redirections_helper(&parts, &len, &i, cmd);
	result = malloc(len + 1);
	result[0] = '\0';
	i = 0;
	while (parts[i])
	{
		if (ft_strcmp(parts[i], "<") != 0 && ft_strcmp(parts[i], ">") != 0
			&& ft_strcmp(parts[i], ">>") != 0
			&& (i == 0 || (ft_strcmp(parts[i - 1], "<") != 0
					&& ft_strcmp(parts[i - 1], ">") != 0
					&& ft_strcmp(parts[i - 1], ">>") != 0)))
		{
			ft_strcat(result, parts[i]);
			ft_strcat(result, " ");
		}
		i++;
	}
	result[len - 1] = '\0';
	free_arr(parts);
	return (result);
}

void	exec_cmd_helper(int fds[2], char **clean_cmd, char *cmd, char ***args)
{
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	*clean_cmd = remove_redirections(cmd);
	*args = ft_split(*clean_cmd, ' ');
}
