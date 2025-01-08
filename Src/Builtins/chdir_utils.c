/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:43:42 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 16:14:19 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

typedef struct s_env_update
{
	char	*new_env_entry;
	size_t	key_len;
	size_t	new_value_len;
	size_t	new_entry_len;
	int		i;
	int		j;
	char	**new_env;
	t_data	*data;
}	t_env_update;

void	initialize_env_update(t_env_update *update, char *key, char *new_value)
{
	if (!key || !new_value)
	{
		printf("Internal error: key or new_value is NULL\n");
		update->data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	update->key_len = strlen(key);
	update->new_value_len = strlen(new_value);
	update->new_entry_len = update->key_len + update->new_value_len + 2;
	update->new_env_entry = NULL;
	update->new_env = NULL;
	update->i = 0;
	update->j = 0;
}

void	not_found(t_env_update *update, char *key, char *new, t_data *data)
{
	update->new_env_entry = malloc(update->new_entry_len);
	if (!update->new_env_entry)
	{
		exit_status_helper("malloc", 1, data);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(update->new_env_entry, key);
	update->new_env_entry[update->key_len] = '=';
	ft_strcpy(update->new_env_entry + update->key_len + 1, new);
	update->new_env[update->j++] = update->new_env_entry;
}

void	set_env_helper(char **env, char *key, t_env_update *update, char *new)
{
	int	found;

	found = 0;
	while (env[update->i] != NULL)
	{
		if (ft_strncmp(env[update->i], key, update->key_len) == 0
			&& env[update->i][update->key_len] == '=')
		{
			free(env[update->i]);
			update->new_env_entry = malloc(update->new_entry_len);
			if (!update->new_env_entry)
				exit(EXIT_FAILURE);
			ft_strcpy(update->new_env_entry, key);
			update->new_env_entry[update->key_len] = '=';
			ft_strcpy(update->new_env_entry + update->key_len + 1, new);
			update->new_env[update->j++] = update->new_env_entry;
			found = 1;
		}
		else
			update->new_env[update->j++] = env[update->i];
		update->i++;
	}
	if (!found)
		not_found(update, key, new, update->data);
}

void	my_set_env(char ***env, char *key, char *new_value, t_data *data)
{
	t_env_update	update;
	size_t			current_env_size;

	current_env_size = 0;
	initialize_env_update(&update, key, new_value);
	while ((*env)[current_env_size] != NULL)
		current_env_size++;
	update.new_env = malloc(sizeof(char *) * (current_env_size + 2));
	if (!update.new_env)
	{
		exit_status_helper("malloc", 1, data);
		exit(EXIT_FAILURE);
	}
	set_env_helper(*env, key, &update, new_value);
	update.new_env[update.j] = NULL;
	free(*env);
	*env = update.new_env;
}

void	change(t_data *data, char *value_PWD, char *value_OLDPWD)
{
	my_set_env(&data->env, "PWD", value_PWD, data);
	my_set_env(&data->env, "OLDPWD", value_OLDPWD, data);
	my_set_env(&data->env2, "PWD", value_PWD, data);
	my_set_env(&data->env2, "OLDPWD", value_OLDPWD, data);
}
