/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:17:25 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/04 11:34:49 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**heredoc_helper(int count, char **args, int *new_count)
{
	int		i;
	int		j;
	int		cmd_found;
	char	**new_args;

	init_heredoc_helper(&new_args, &i, &j, count);
	cmd_found = 0;
	while (++i < count)
	{
		if (ft_strcmp(args[i], "<<") == 0)
			heredoc_cmd_found(&new_args, &j, &i, &cmd_found);
		else
			new_args[j++] = ft_strdup(args[i]);
	}
	new_args[j] = NULL;
	*new_count = j;
	return (new_args);
}

void	processing_helper(t_data *data, char *rl, int fd, char *key)
{		
	if (data->heredoc_args == NULL)
	{
		perror("Error splitting input");
		data->exit_status = 1;
		free(rl);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (data->quotes == 0)
		var_in_env(&rl, data->env, data);
	if (ft_strcmp(data->heredoc_args[0], key) != 0)
	{
		if (write(fd, rl, strlen(rl)) < 0 || write(fd, "\n", 1) < 0)
		{
			perror("Error writing to file");
			data->exit_status = 1;
			free(rl);
			close(fd);
			free_arr(data->heredoc_args);
			exit(EXIT_FAILURE);
		}
	}
	free(rl);
	free_arr(data->heredoc_args);
}

void	heredoc_prcessing(t_data *data, int fd, char *rl, char *key)
{
	while (1)
	{
		rl = readline("> ");
		if (rl == NULL)
		{
			perror("Error reading input");
			data->exit_status = 1;
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (*rl == '\0')
		{
			free(rl);
			continue ;
		}
		data->heredoc_args = ft_split_2(rl, ' ');
		if (ft_strcmp(data->heredoc_args[0], key) == 0)
		{
			free_arr(data->heredoc_args);
			free(rl);
			break ;
		}
		processing_helper(data, rl, fd, key);
	}
}

void	heredoc_continue(t_data *data, char **new_arg)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (new_arg[++i])
	{
		if (check_s_equal(new_arg[i], ">>"))
		{
			exec_heredoc(data, new_arg);
			j = 1;
			break ;
		}
	}
	if (j != 1)
		how_to_continue(data, new_arg);
}

void	heredoc(char **args, char *key, int count, t_data *data)
{
	char	*rl;
	int		fd;
	int		new_count;
	char	**new_arg;

	rl = NULL;
	data->heredoc_args = NULL;
	fd = open("heredoc_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free_arr(data->heredoc_args);
		perror("Error opening file");
		exit_status_exit(1, 1, data);
	}
	heredoc_prcessing(data, fd, rl, key);
	close(fd);
	new_arg = heredoc_helper(count, args, &new_count);
	if (new_arg == NULL)
	{
		free_arr(data->heredoc_args);
		perror("ERROR");
		exit_status_exit(1, 1, data);
	}
	heredoc_continue(data, new_arg);
	free_arr(new_arg);
}
