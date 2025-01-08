/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtins_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:42:50 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/04 11:34:59 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	my_exit_helper(char *s, t_data *data)
{
	char	**a;

	a = ft_split_2(s, ' ');
	my_exit(a, data);
}

void	my_exit_helper2(t_data *data)
{
	char	*shlvl_str;

	data->shlvl--;
	shlvl_str = ft_itoa(data->shlvl);
	my_set_env(&data->env, "SHLVL", shlvl_str, data);
	my_set_env(&data->env2, "SHLVL", shlvl_str, data);
	free(shlvl_str);
}

void	free_helper(char **args, t_data *data)
{
	free_arr(args);
	free_data_2(data);
	rl_clear_history();
}

int	exp_arg_check2(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&& !(str[0] >= 'A' && str[0] <= 'Z')
		&&str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!is_ok(str[i]))
			return (0);
		i++;
	}
	return (1);
}
