/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2025/01/04 12:05:23 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdarg.h>
# include "../libft/libft.h"

# ifndef HISTORY_SIZE
#  define HISTORY_SIZE 100
# endif

typedef struct s_data
{
	char	**env;
	char	**env2;
	char	**history;
	int		history_count;
	char	**cmds;
	char	*previous;
	char	**heredoc_args;
	int		shlvl;
	char	*temp_pwd;
	int		quotes;
	int		exit_status ;
}	t_data;

typedef struct s_her_data{
	int		i;
	char	*key;
	char	*temp_file;
	char	*line;
	char	*cmd_tmp;
	int		s;
	int		f;
	int		y;
	int		fd;
}	t_her_data;

typedef struct s_pipe
{
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		save_std[2];
}	t_pipe;

extern int	g_s;

int	countWords(const char *str);
int	notInQuotes(char *str, char *toFind);

/* minishell_utils.c */
void	free_arr(char **input);
void	free_data(t_data *data);
void	handle_spaces(char *input, char **ret, int i[3]);
int		handle_quote(char *input, char **ret, int i[3], char quote);
void	free_data_2(t_data *data);

/* minishell_helper.c */
void	init_data_helper(t_data **data, char **env);
int		ft_strlen_2(char **c);
int		check_trim(char *input);
void	init_data_helper2(t_data **data, char **env);
void	init_help(t_data **data, char **env);

/* delete_spaces.c */
char	*delete_spaces(char *input, t_data *data);

/* process_input.c */
void	process_input(char *input, t_data *data);

/* process_input_utils.c */
// void	remove_ttq_helper(char *temp, t_data *data, int j[2], int i);

/* ft_split_2.c */
char	**ft_split_2(char *s, char c);

/* ft_split_2_utils.c */
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		is_delimiter(char c, char delimiter);
void	toggle_quote(int *in_quotes, char *quote_char, char current_char);

/* signal.c */
void	handle_sigint(int sig);
void	setup_signals(void);
void	ignore_signals(void);
void	restore_signals(void);

/* exec.c */
void	how_to_exec(t_data *data);
void	exec(t_data *data, char *cmd);
void	exec_heredoc(t_data *data, char **cmd);
void	exec_redir(t_data *data, char *cmd);
void	exec_pipe(t_data *data, char *cmd);
void	exec_heredoc_helper(t_data *data, char *cmd);

/* exec_utils.c */
void	exec_cmd(t_data *data, char **args);
void	exec_helper(t_data *data, char **args);
int		check_s_equal(char *s, char *d);
void	exec_splitter(t_data *data, char **args);
void	exec_splitter_helper(t_data *data, char ***args, int *f);

/* exec_utils_helper.c */
void	how_to_continue(t_data *data, char **cmds);
char	*get_file(char **cmds, char *sign);
void	init_args_to_heredoc(t_data *data, int i, char **cmds);
void	free_exec_heredoc(char *key, char *file);
void	exec_append_skipper(t_data *data, char **cmds);

/* exec_utils_helper_2.c */
void	add_necessary_sp(t_data *data, int i);
void	add_double_sp_doc(t_data *data, int i, int *j);
void	add_single_sp_doc(t_data *data, int i, int *j);
void	add_double_sp(t_data *data, int i, int j);
void	add_single_sp(t_data *data, int i, int j);

/* exec_utils_helper_3.c */
int		check_s_equal(char *s, char *d);
char	*ft_strcat(char *dest, const char *src);
char	*rejoin_args(char **args, t_data *data);

/* exec_heredoc_utils */
void	last_exec_heredoc_helper(char **cmds, int i[2]);
void	last_heredoc_helper(char ***last, char **cmds, int i[4], t_data *data);
void	last_exec_heredoc(t_data *data, char **cmds);
void	exec_heredoc_skipper(t_data *data, char **cmds, int c);
void	exec_heredoc_helper(t_data *data, char *cmd);

/* remove_quote.c */
void	remove_ttq_helper(char *temp, char **cmd, int i[3]);
void	remove_ttq_s(char *temp, char **cmd, int i[3]);
void	exit_remove(t_data *data, char **args, char *temp);
void	remove_quote(t_data *data, char **args);

/* handle_pipes.c */
void	close_pipes(int **pipes, int cmd_count);
void	create_pipes(int count, int ***pipes, t_data *data);
void	exec_splitter_pipe(t_data *data, char **args);
void	exec_cmd_pipes(t_data *data, char **cmds, int **pipes, int i);
void	handle_pipes(t_data *data, char **cmds, int count);

/* handle_pipes_utils.c*/
void	where_to_go(t_data *data, char *cmd);
void	exec_helper_pipes(t_data *data, char **args, int save_std[2]);
void	child_process(int i, int **pipes, char **cmds);
void	parent_process(int i, int **pipes, char **cmds, char **args);

/* handle_pipes_helper.c */
void	exec_pipe_redir(char **cmds, t_data *data, int **pipes, int i);
void	free_and_exit_pipe(char **cmds, char **args, int **pipes, t_data *data);

/* get_env.c */
char	*find_command_path(char *command, char **envp, t_data *data);
char	*join_path_command(char *path, char *command);
char	*get_path_env(char **envp);

/* chdir.c */
void	cd(char **args, int count, t_data *data, char **previous);
void	path_exist(char *target, char *current, char **previous, t_data *data);

/* chdir_utils.c */
void	my_set_env(char ***env, char *key, char *new_value, t_data *data);
void	change(t_data *data, char *value_PWD, char *value_OLDPWD);

/* echo.c */
void	echo(char **arg, int count, t_data *data);

/* exit.c */
void	my_exit(char **args, t_data *data);
void	my_exit2(char **args, t_data *data);
void	my_exit_helper(char *s, t_data *data);
void	my_exit_helper2(t_data *data);

/* env.c */
void	env(char **envp, t_data *data);
void	env2(char **envp, t_data *data);

/* pwd.c */
void	pwd(int count, t_data *data);
void	path_helper2(t_data *data, char **updated_path);

/* exprt.c */
char	**export(char **args, int count, char **new_env, t_data *data);
int		exp_arg_check(char *str);

/* exprt2.c */
char	**export2(char **args, int count, char **new_env, t_data *data);

/* export_helper.c*/
void	free_env(char **env);
int		is_valid_export_arg(char *arg);
int		len(char *str);

/* unset_helper.c*/
int		count_env_vars(char **env);
char	**create_new_env(int count, t_data *data);
int		copy_env_var(char **new_env, char *env_var, int index);

/* unset.c */
char	**unset(char **args, int count, char **env, t_data *data);
char	**unset2(char **args, int count, char **env, t_data *data);

/* builtins_helper.c */
int		env_helper(char **copied_env, int i, int j, t_data *data);
char	*get_path(const char *cmd, char **envp, t_data *data);
char	*ft_strcpy(char *dest, const char *src);

/* builtins_helper2.c */
void	path_exist_helper(t_data *data, char *new_pwd, char *target);
void	exit_error_print(int exit_status, char *str, t_data *data);
void	home2_case(char **args, t_data *data, char	*current, char **previous);
int		is_numeric(char *arg);
void	update_env(t_data *data, char *key, char *value);

/* builtins_helper3.c */
void	my_exit_helper(char *s, t_data *data);
void	my_exit_helper2(t_data *data);
void	free_helper(char **args, t_data *data);
int		exp_arg_check2(char *str);

/* ft_split_3.c */
char	**ft_split_3(char *s, char c);

/* sort.c */
char	**bubble_sort(char **arr, int n);

/* redirection_output/input.c */
void	redirect_output(char **args, char *output, int count, t_data *data);
void	redirect_input(char **args, char *input_file, int count, t_data *data);
int		init_redirect(int i[2], int *count, int *cmd_found, char ***new_args);
void	free_redir(char **new_args, t_data *data, char **args, char *output);
void	free_redir_parent(char **args, char **new_args);
int		is_operation(char c);

/* heredoc.c */
void	heredoc(char **args, char *key, int count, t_data *data);

/* heredoc_helper.c */
void	init_heredoc_helper(char ***new_args, int *i, int *j, int count);
void	heredoc_cmd_found(char ***new_args, int *j, int *i, int *cmd_found);
void	exit_status_exit(int status, int for_exit, t_data *data);
int		is_quoted(char *str);

/* append.c */
void	redirect_append(char **args, char *output, int count, t_data *data);

/* exit_status.c*/
int		exit_error_int(int exit_status, int returned, t_data *data);
void	exit_status_helper(char *str, int i, t_data *data);
void	exit_status_return(int i, t_data *data);
char	*exit_error_char(int exit_status, char *returned, t_data *data);
char	**exit_error_2char(int exit_status, char **returned, t_data *data);

/* dolar_helper.c */
int		is_ok(char c);
int		is_ok2(char c);
char	*add_equal(char *str);
char	*env_search(char *str, char **env);
void	edit_str(char **str, int start, int end, char *env_value);

/* dolar_helper2.c */
char	*rm_dl(char *str, t_data *data);
void	var_ret_helper1(char *str, int *i, int *double_quotes);
int		helper2(char *str, int *i, int *index);
char	*helper3(char *str, int *i, int *index);

/* dolar.c */
void	var_in_env(char **str, char **env, t_data *data);

/* norm1.c */
void	open_file(char *output, t_data *data);
void	exec_cmd_free(char **args, t_data *data);
void	ft_strdup_2(t_data *data, char **to_dup);
void	free_redir(char **new_args, t_data *data, char **args, char *output);
void	check_redir(char **cmds, t_data *data, char *file, int i);

/* norm2.c */
void	close_pipes(int **pipes, int cmd_count);
void	create_pipes(int count, int ***pipes, t_data *data);
void	setup_child_pipes(int i, int cmd_count, int **pipes);
void	close_unused_pipes(int i, int cmd_count, int **pipes);
char	*get_key(char *s);

/* norm3.c */
void	free_and_return(char *temp, t_data *data);
void	save_std_fds(int *saved_stdin, int *saved_stdout);
void	remove_char(char *str, char ch);
void	handle_builtin_commands(t_data *data, char **args);
void	exec_splitter_pipe(t_data *data, char **args);

/* norm4.c */
void	double_unset(t_data *data, char **args);
void	open_input_file(char *input, t_data *data);
void	last_exec_heredoc_helper(char **cmds, int i[2]);
int		copy_heredoc_parts(char ***last, char **cmds, int *i);
void	last_heredoc_helper(char ***last, char **cmds, int i[4], t_data *data);

/* norm5.c */

void	handle_cmd_conditions(char **cmds, int **i, char **last);
void	exec_child_process(t_data *data, char **args);
void	handle_command_not_found(char **args, t_data *data);
void	is_directory(char *cmd_path, t_data *data);
char	*trim_whitespace(char *str);

/* norm6.c */
int		is_valid_redirection(char **cmds, int i);
int		process_redirection(char **cmds, int i, t_data *data, char **key);
void	process_redirection_tokens(char **cmds, t_data *data, int *redir_count);
void	process_redirection_actions(char **cmds, t_data *data, int i);
int		quotes_key(char *str);

/* norm7.c */
void	g_s_helper(t_data *data);
void	add_space_before_double_sp(t_data *data, int i, int *k, char *temp);
void	ad_singel_helper2(t_data *data, int i, int *k, char *temp);
void	ad_double_helper(t_data *data, int i, int *k, char *temp);
void	ad_singel_helper(t_data *data, int i, int *k, char *temp);

/* norm8.c */
void	add_necessary_helper(t_data *data, int i, int j);
void	execute_command(t_data *data, char *cmd, int save_std[2]);
char	*ft_strreplace(char *str, char *old, char *new);
void	her_help(t_her_data *data_her, char **cmds);
void	her_pipe_process(t_her_data *data_her);

/* norm9.c */
void	open_test(int f);
void	handle_redirections(char *cmd, int *input_fd, int *o_f);
void	remove_redirections_helper(char ***parts, int *len, int *i, char *cmd);
char	*remove_redirections(char *cmd);
void	exec_cmd_helper(int fds[2], char **clean_cmd, char *cmd, char ***args);

/* main.c */
void	init_data_cmds(char **commands, t_data *data);
void	handle_input(char *input, t_data *data);

#endif