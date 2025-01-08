/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:39:01 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/01 13:52:27 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	rm_dl_helper(char *str, int i[2], char *wd, int qf)
{
	if (str[i[0]] == '"' && qf == 0)
		qf = 1;
	else if (str[i[0]] == '"' && qf == 1)
		qf = 0;
	if (str[i[0]] == '$' && (str[i[0] + 1] == '$' || str[i[0] + 1] == '?'))
	{
		wd[i[1]++] = str[i[0]++];
		wd[i[1]++] = str[i[0]++];
	}
	else if (str[i[0]] == '$' && !is_ok2(str[i[0] + 1]) && str[i[0] + 1] != '\''
		&& str[i[0] + 1] != '"' && str[i[0] + 1] != '\0')
		i[0] += 2;
	else if (str[i[0]] == '$' && (str[i[0] + 1] == '\'' || str[i[0] + 1] == '"')
		&& i[0] != 0 && (str[i[0] - 1] != '\'' && str[i[0] - 1] != '"')
		&& qf != 1)
		i[0]++;
	else if (str[i[0]] == '$' && i[0] == 0 && (str[i[0] + 1] == '\''
			|| str[i[0] + 1] == '"'))
		i[0]++;
	else
	{
		wd[i[1]] = str[i[0]];
		i[0]++;
		i[1]++;
	}
}

char	*rm_dl(char *str, t_data *data)
{
	int		i[2];
	int		qf;
	char	*wd;

	i[0] = 0;
	i[1] = 0;
	qf = 0;
	if (ft_strchr(str, '$'))
	{
		wd = malloc(ft_strlen(str) + 1);
		if (!wd)
		{
			free(str);
			return (exit_error_char(EXIT_FAILURE, NULL, data));
		}
		i[0] = 0;
		while (str[i[0]] != '\0')
			rm_dl_helper(str, i, wd, qf);
		wd[i[1]] = '\0';
		free(str);
		return (wd);
	}
	return (str);
}

void	var_ret_helper1(char *str, int *i, int *double_quotes)
{
	if (*double_quotes == 0 && str[*i] == '"')
	{
		*double_quotes = 1;
		(*i)++;
	}
	else if (*double_quotes == 1 && str[*i] == '"')
	{
		*double_quotes = 0;
		(*i)++;
	}
	else if (str[*i] == '\'' && *double_quotes == 0)
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
		if (str[*i] != '\0')
			(*i)++;
	}
}

int	helper2(char *str, int *i, int *index)
{
	if (*i != 0 && str[*i - 1] == '\\')
	{
		remove_char(str, '\\');
		if (str[*i] != '\0')
			(*i)++;
		return (0);
	}
	index[0] = *i + 1;
	if (str[*i] != '\0')
		(*i)++;
	if (!(str[*i] >= 'a' && str[*i] <= 'z') && !(str[*i] >= 'A'
			&& str[*i] <= 'Z'))
	{
		if (str[*i] != '\0')
			(*i)++;
		return (0);
	}
	while (str[*i] != '\0' && is_ok(str[*i]))
		(*i)++;
	index[1] = *i;
	return (1);
}

char	*helper3(char *str, int *i, int *index)
{
	int	double_quotes;

	double_quotes = 0;
	while (str[*i] != '\0')
	{
		var_ret_helper1(str, i, &double_quotes);
		if (str[*i] == '$')
		{
			if (str[*i + 1] == '$' || str[*i + 1] == '?')
			{
				*i += 2;
				if (str[*i - 1] == '$')
					return ("$$");
				else
					return ("$?");
			}
			if (helper2(str, i, index) == 0)
				return (NULL);
			if (index[0] == index[1])
				continue ;
			break ;
		}
		(*i)++;
	}
	return (str);
}
