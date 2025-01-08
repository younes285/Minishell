/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:08:31 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/01 16:39:16 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	init_data(t_data **data, char **env)
{
	int	i;

	*data = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		(*data)->exit_status = 1;
		exit(1);
	}
	(*data)->history = (char **)malloc(sizeof(char *) * (HISTORY_SIZE + 1));
	if (!((*data)->history))
	{
		free(*data);
		exit(1);
	}
	setup_signals();
	i = -1;
	while (++i <= HISTORY_SIZE)
		(*data)->history[i] = NULL;
	(*data)->previous = NULL;
	(*data)->heredoc_args = NULL;
	init_data_helper(data, env);
	init_data_helper2(data, env);
	(*data)->history_count = 0;
	init_help(data, env);
}

void	init_data_cmds(char **commands, t_data *data)
{
	int	i;
	int	l;

	l = ft_strlen_2(commands);
	(data)->cmds = (char **)malloc(sizeof(char *)
			* (l + 1));
	if (!(data)->cmds)
	{
		free_arr(commands);
		free(data);
		ft_putendl_fd("Error: Memory allocation failed", 2);
		data->exit_status = 1;
		exit(1);
	}
	i = 0;
	while (i <= l)
	{
		(data)->cmds[i] = NULL;
		i++;
	}
}

void	add_to_history(t_data *data, char *input)
{
	if (data->history_count == HISTORY_SIZE)
	{
		free(data->history[0]);
		ft_memmove(data->history, data->history + 1,
			(HISTORY_SIZE - 1) * sizeof(char *));
		data->history_count--;
	}
	data->history[data->history_count] = ft_strdup(input);
	data->history_count++;
	add_history(input);
}

void	handle_input(char *input, t_data *data)
{
	if (*input)
	{
		add_to_history(data, input);
		process_input(input, data);
		how_to_exec(data);
		free_arr(data->cmds);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	*data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			rl_clear_history();
			my_exit_helper("exit", data);
			break ;
		}
		data->quotes = quotes_key(input);
		if (check_trim(input) == 0)
			continue ;
		g_s_helper(data);
		handle_input(input, data);
	}
	return (data->exit_status);
}
