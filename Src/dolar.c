/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:03:30 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/03 19:55:19 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*var_ret(char *str, int *i, t_data *data)
{
	int		index[2];
	char	*temp;
	char	*result;

	index[0] = -1;
	index[1] = 0;
	result = helper3(str, i, index);
	if (result == NULL)
		return (NULL);
	if (ft_strcmp(result, "$?") == 0)
		return (ft_strdup("$?"));
	if (index[0] == -1 || index[0] == index[1])
		return (NULL);
	temp = (char *)malloc((index[1] - index[0] + 1) * sizeof(char));
	if (!temp)
		return (exit_error_char(1, NULL, data));
	ft_strncpy(temp, str + index[0], index[1] - index[0]);
	temp[index[1] - index[0]] = '\0';
	return (temp);
}

void	var_in_env_helper(char *var_name, char **env_value, int *i, char **env)
{
	if (check_s_equal(var_name, "$?"))
	{
		*env_value = ft_itoa(i[3]);
		i[1] = i[0] - ft_strlen(var_name);
	}
	else
	{
		*env_value = env_search(var_name, env);
		if (*env_value != NULL)
			*env_value = ft_strdup(*env_value);
		i[1] = i[0] - ft_strlen(var_name) - 1;
	}
}

void	handle_quotes(char **str, int *i)
{
	if ((*str)[i[0]] == '"' && i[2] != 2)
	{
		if (i[2] == 1)
			i[2] = 0;
		else
			i[2] = 1;
	}
	else if ((*str)[i[0]] == '\'' && i[2] != 1)
	{
		if (i[2] == 2)
			i[2] = 0;
		else
			i[2] = 2;
	}
}

void	process_var(char **str, char **env, t_data *data, int *i)
{
	char	*var_name;
	char	*env_value;

	env_value = NULL;
	var_name = var_ret(*str, &i[0], data);
	if (var_name)
	{
		var_in_env_helper(var_name, &env_value, i, env);
		if (env_value == NULL)
        {

            if (i[1] > 0 && (*str)[i[1] - 1] == ' ')
                edit_str(str, i[1] - 1, i[0], NULL);
            else
                edit_str(str, i[1], i[0], NULL);
        }
		else
			edit_str(str, i[1], i[0], env_value);
		free(var_name);
		if (env_value)
		{
			free(env_value);
			env_value = NULL;
			i[0] = i[1];
		}
	}
}

void	var_in_env(char **str, char **env, t_data *data)
{
	int	i[4];

	i[0] = 0;
	i[2] = 0;
	i[3] = data->exit_status;
	*str = rm_dl(*str, data);
	printf("from var in env : |%s|\n", *str);
	while (i[0] < (int)ft_strlen(*str) && (*str)[i[0]] != '\0')
	{
		handle_quotes(str, i);
		if ((*str)[i[0]] == '$' && i[2] != 2)
			process_var(str, env, data, i);
		else
			i[0]++;
	}
}
