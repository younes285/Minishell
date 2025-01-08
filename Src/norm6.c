/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:34:07 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/01 18:50:41 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_valid_redirection(char **cmds, int i)
{
	if (!cmds[i + 1] || cmds[i + 1][0] == '\0' ||
		is_operation(cmds[i + 1][0]) || check_s_equal(cmds[i + 1], "") ||
		ft_strlen(cmds[i + 1]) == 0)
		return (0);
	return (1);
}

int	process_redirection(char **cmds, int i, t_data *data, char **key)
{
	*key = ft_strdup((const char *)cmds[i + 1]);
	if (!(*key))
	{
		printf("bash: memory allocation error\n");
		data->exit_status = 1;
		return (1);
	}
	heredoc(cmds, *key, ft_strlen_2(cmds), data);
	return (0);
}

void	process_redirection_tokens(char **cmds, t_data *data, int *redir_count)
{
	int		i;
	char	*trimmed;

	i = -1;
	while (cmds[++i])
	{
		trimmed = trim_whitespace(cmds[i]);
		if (!trimmed || trimmed[0] == '\0')
		{
			free(trimmed);
			continue ;
		}
		if (check_s_equal(trimmed, ">") || check_s_equal(trimmed, "<"))
		{
			if (!is_valid_redirection(cmds, i))
			{
				printf("bash: syntax error near unexpected token \n");
				data->exit_status = 2;
				free(trimmed);
				return ;
			}
			(*redir_count)++;
		}
		free(trimmed);
	}
}

void	process_redirection_actions(char **cmds, t_data *data, int i)
{
	char	*file;
	char	*trimmed;

	trimmed = trim_whitespace(cmds[i]);
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return ;
	}
	if (check_s_equal(trimmed, ">") || check_s_equal(trimmed, "<"))
	{
		file = get_file(cmds, cmds[i]);
		if (file)
			check_redir(cmds, data, file, i);
		else
		{
			printf("bash: syntax error near unexpected token");
			data->exit_status = 1;
		}
	}
	free(trimmed);
}

int	quotes_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			if (str[i] == '"' || str[i] == '\'')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
