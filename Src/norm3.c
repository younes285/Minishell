/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:29:02 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/01 14:39:28 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_and_return(char *temp, t_data *data)
{
	if (!temp)
	{
		data->exit_status = 1;
		free_data(data);
		return ;
	}
}

void	remove_char(char *str, char ch)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ch)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	handle_builtin_commands(t_data *data, char **args)
{
	if (check_s_equal(args[0], "cd") == 1)
		cd(args, ft_strlen_2(args) - 1, data, &data->previous);
	else if (check_s_equal(args[0], "exit") == 1)
	{
		free_arr(data->cmds);
		my_exit2(args, data);
	}
	else if (check_s_equal(args[0], "env") == 1)
		env(data->env, data);
	else if (check_s_equal(args[0], "pwd") == 1)
		pwd(ft_strlen_2(args) - 1, data);
	else if (check_s_equal(args[0], "echo") == 1)
		echo(args, ft_strlen_2(args), data);
	else if (check_s_equal(args[0], "export") == 1 && ft_strlen_2(args) > 1)
	{
		data->env = export(args, ft_strlen_2(args), data->env, data);
		data->env2 = export2(args, ft_strlen_2(args), data->env2, data);
	}
	else if (check_s_equal(args[0], "export") == 1 && ft_strlen_2(args) == 1)
		env2(data->env2, data);
	else if (check_s_equal(args[0], "unset") == 1)
		double_unset(data, args);
}

void	exec_splitter_pipe(t_data *data, char **args)
{
	char	*shlvl_str;

	handle_builtin_commands(data, args);
	if (check_s_equal(args[0], "./minishell"))
	{
		data->shlvl++;
		shlvl_str = ft_itoa(data->shlvl);
		my_set_env(&data->env, "SHLVL", shlvl_str, data);
		my_set_env(&data->env2, "SHLVL", shlvl_str, data);
		free(shlvl_str);
		exec_helper(data, args);
		my_exit_helper2(data);
	}
}
