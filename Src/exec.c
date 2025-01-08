/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:13:25 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/08 22:44:24 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec(t_data *data, char *cmd)
{
	char	**args;
	int		y = countWords(cmd);

	printf("from exec : %i, |%s|\n", y, cmd);
	if (y == 1)
	{
		args = (char **)malloc(sizeof(char *) * (2));
		args[0] = ft_strdup((const char *)cmd);
		args[1] = NULL;
	}
	else
		args = ft_split_2(cmd, ' ');
	if (!args)
	{
		free_data(data);
		exit(1);
	}
	exec_splitter(data, args);
	if (args)
		free_arr(args);
}

void	exec_pipe(t_data *data, char *cmd)
{
	int		i;
	char	**cmds;

	i = 0;
	if (cmd[0] == '|' || cmd[strlen(cmd) - 1] == '|' || strstr(cmd, "||"))
	{
		printf("bash: syntax error near unexpected token `|'\n");
		exit_status_return(1, data);
	}
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (i == 0 || is_operation(cmd[i - 2]) || cmd[i + 1] == '\0')
			{
				printf("bash: syntax error near unexpected token `|'\n");
				data->exit_status = 1;
				return ;
			}
		}
		i++;
	}
	cmds = ft_split_2(cmd, '|');
	remove_quote(data, cmds);
	handle_pipes(data, cmds, ft_strlen_2(cmds));
}

void	exec_heredoc(t_data *data, char **cmds)
{
	char	*file;
	int		i;
	char	*key;

	file = NULL;
	key = NULL;
	i = -1;
	while (cmds[++i])
	{	
		if (check_s_equal(cmds[i], ">>") || check_s_equal(cmds[i], "<<"))
		{
			if (check_s_equal(cmds[i], ">>"))
			{
				file = ft_strdup((const char *)cmds[i + 1]);
				redirect_append(cmds, file, ft_strlen_2(cmds), data);
			}
			else
			{
				if (process_redirection(cmds, i, data, &key) == 1)
					break ;
			}
			free_exec_heredoc(key, file);
			break ;
		}
	}
}

void	exec_redir(t_data *data, char *cmd)
{
	char	**cmds;
	int		redir_count;
	int		i;

	cmds = ft_split_2(cmd, ' ');
	if (!cmds)
	{
		printf("Error: Failed to split the command.\n");
		return ;
	}
	remove_quote(data, cmds);
	redir_count = 0;
	process_redirection_tokens(cmds, data, &redir_count);
	if (redir_count > 0)
	{
		i = -1;
		while (cmds[++i])
		{
			process_redirection_actions(cmds, data, i);
		}
	}
	free_arr(cmds);
}

void	how_to_exec(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i] != NULL)
	{
		add_necessary_sp(data, i);
		if (ft_strchr(data->cmds[i], '$'))
			var_in_env(data->cmds, data->env, data);
		if (ft_strchr((const char *)data->cmds[i], '|') && notInQuotes(data->cmds[i], "|"))
			exec_pipe(data, data->cmds[i]);
		else if ((ft_strstr(data->cmds[i], "<<") && notInQuotes(data->cmds[i], "<<"))
			|| (ft_strstr(data->cmds[i], ">>") && notInQuotes(data->cmds[i], ">>")))
			exec_heredoc_helper(data, data->cmds[i]);
		else if ((ft_strchr((const char *)data->cmds[i], '<') && notInQuotes(data->cmds[i], "<"))
			|| (ft_strchr((const char *)data->cmds[i], '>') && notInQuotes(data->cmds[i], ">")))
			exec_redir(data, data->cmds[i]);
		else
			exec(data, data->cmds[i]);
		i++;
	}
}
