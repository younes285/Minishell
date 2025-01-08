/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:46:30 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/04 11:35:16 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec_cmd(t_data *data, char **args)
{
	char	*cmd_path;
	int		exec_status;

	cmd_path = find_command_path(args[0], data->env, data);
	if (cmd_path == NULL)
	{
		cmd_path = find_command_path(args[0], data->env2, data);
		if (cmd_path == NULL)
			handle_command_not_found(args, data);
		exec_status = execve(cmd_path, args, data->env2);
	}
	else
		exec_status = execve(cmd_path, args, data->env);
	is_directory(cmd_path, data);
	if (exec_status == -1)
	{
		perror("execve");
		exec_cmd_free(args, data);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
}

void	exec_helper(t_data *data, char **args)
{
	pid_t	pid1;
	int		status;

	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		exec_child_process(data, args);
	else
	{
		ignore_signals();
		if (waitpid(pid1, &status, 0) == -1)
		{
			perror("waitpid");
			free_data(data);
			exit(1);
		}
		setup_signals();
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status) + 128;
	}
}

void	exec_splitter_helper2(t_data *data, char **args, int *f)
{
	if (check_s_equal(args[0], "cd") == 1)
		cd(args, ft_strlen_2(args) - 1, data, &data->previous);
	else if (check_s_equal(args[0], "!") == 1)
		printf("\n");
	else if (check_s_equal(args[0], "exit") == 1)
	{
		if (ft_strlen_2(args) <= 2)
			free_arr(data->cmds);
		my_exit(args, data);
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
	else
		*f = 0;
}

void	exec_splitter_helper(t_data *data, char ***args, int *f)
{
	char	*str;

	str = rejoin_args(*args, data);
	if (!str)
	{
		data->exit_status = 1;
		return ;
	}
	if (ft_strchr(str, '$'))
		var_in_env(&str, data->env, data);
	int		y = countWords(str);
	printf("from exec_splitter helper : %i, |%s|\n", y, str);
	if (y == 1)
	{
		*args = (char **)malloc(sizeof(char *) * (2));
		(*args)[0] = ft_strdup((const char *)str);
		(*args)[1] = NULL;
	}
	else
		*args = ft_split_2(str, ' ');
	if (!(*args))
	{
		data->exit_status = 1;
		return ;
	}
	remove_quote(data, *args);
	exec_splitter_helper2(data, *args, f);
	free (str);
}

void	exec_splitter(t_data *data, char **args)
{
	int		f;
	char	*shlvl_str;

	f = 1;
	exec_splitter_helper(data, &args, &f);
	if (f == 0)
	{
		if (check_s_equal(args[0], "unset") == 1)
			double_unset(data, args);
		else if (check_s_equal(args[0], "./minishell"))
		{
			data->shlvl++;
			shlvl_str = ft_itoa(data->shlvl);
			my_set_env(&data->env, "SHLVL", shlvl_str, data);
			my_set_env(&data->env2, "SHLVL", shlvl_str, data);
			free(shlvl_str);
			exec_helper(data, args);
			my_exit_helper2(data);
		}
		else
			exec_helper(data, args);
	}
	free_arr(args);
}
