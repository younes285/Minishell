/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:38:32 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/02 14:08:26 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	add_necessary_helper(t_data *data, int i, int j)
{
	if (j > 0 && data->cmds[i][j - 1] && data->cmds[i][j + 2]
	&& data->cmds[i][j - 1] != ' ' && data->cmds[i][j + 2] != ' ')
		add_double_sp_doc(data, i, &j);
	else if ((j > 0 && data->cmds[i][j - 1] && data->cmds[i][j - 1] != ' ')
	|| (data->cmds[i][j + 2] && data->cmds[i][j + 2] != ' '))
		add_single_sp_doc(data, i, &j);
}

void	execute_command(t_data *data, char *cmd, int save_std[2])
{
	char	**args;
	char	*clean_cmd;
	int		fds[2];

	fds[0] = -1;
	fds[1] = -1;
	if (ft_strchr(cmd, '$'))
		var_in_env(&cmd, data->env, data);
	handle_redirections(cmd, &fds[0], &fds[1]);
	exec_cmd_helper(fds, &clean_cmd, cmd, &args);
	if (!args)
		my_exit_helper("Memory allocation failed", data);
	if (ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "exit") == 0
		|| ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "pwd") == 0
		|| ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "export") == 0
		|| ft_strcmp(args[0], "unset") == 0
		|| ft_strcmp(args[0], "./minishell") == 0)
		exec_splitter_pipe(data, args);
	else
		exec_helper_pipes(data, args, save_std);
	free(clean_cmd);
	free_arr(args);
}

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*result;
	char	*ins;
	int		i[4];

	if (!str || !old || !new)
		return (NULL);
	i[0] = ft_strlen(str);
	i[1] = ft_strlen(old);
	i[2] = ft_strlen(new);
	ins = ft_strstr(str, old);
	if (!ins)
		return (ft_strdup(str));
	i[3] = ins - str;
	result = malloc(i[0] - i[1] + i[2] + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, i[3]);
	ft_strcpy(result + i[3], new);
	ft_strcpy(result + i[3] + i[2], str + i[3] + i[1]);
	return (result);
}

void	her_help(t_her_data *data_her, char **cmds)
{
	data_her->s = 0;
	data_her->f = 0;
	data_her->y = ft_strlen(cmds[data_her->i]) - 1;
	while (data_her->y >= 0 && cmds[data_her->i][data_her->y] != '>')
		data_her->y--;
	if (data_her->y >= 0)
	{
		data_her->f = data_her->y + 2;
		data_her->y += 2;
		while (cmds[data_her->i][data_her->y] != '\0'
			&& cmds[data_her->i][data_her->y] != ' ')
			data_her->y++;
		data_her->temp_file = (char *)malloc(data_her->y
				- data_her->f + 2);
		*(data_her->temp_file + data_her->s) = 'v';
		data_her->s++;
		while (data_her->f < data_her->y)
		{
			*(data_her->temp_file + data_her->s)
				= cmds[data_her->i][data_her->f];
			data_her->s++;
			data_her->f++;
		}
		*(data_her->temp_file + data_her->s) = '\0';
	}	
}

void	her_pipe_process(t_her_data *data_her)
{
	while (1)
	{
		data_her->line = readline("> ");
		if (data_her->line
			&& ft_strcmp(data_her->line, data_her->key) == 0)
		{
			free(data_her->line);
			break ;
		}
		if (data_her->line)
		{
			write(data_her->fd, data_her->line, ft_strlen(data_her->line));
			write(data_her->fd, "\n", 1);
			free(data_her->line);
		}
	}
}
