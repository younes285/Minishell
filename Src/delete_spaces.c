/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:12:40 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/03 17:25:18 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	process_quotes(char *input, char **ret, int i[3])
{
	if (input[i[0]] == '\'')
	{
		if (!handle_quote(input, ret, i, '\''))
			return (0);
	}
	else if (input[*i] == '\"')
	{
		if (!handle_quote(input, ret, i, '\"'))
			return (0);
	}
	return (1);
}

void	skip_first_last(char *input, int i[3])
{
	i[2] = ft_strlen(input) - 1;
	while (input[i[0]] == ' ')
		i[0]++;
	while (input[i[2]] == ' ')
		i[2]--;
	i[2]++;
}

char	*delete_spaces(char *input, t_data *data)
{
	int		i[3];
	char	*ret;

	if (!input)
		return (exit_error_char(1, NULL, data));
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	skip_first_last(input, i);
	ret = (char *)malloc(sizeof(char) * (i[2] + 1));
	if (!ret)
		return (exit_error_char(1, NULL, data));
	while (input[i[0]] && i[0] < i[2])
	{
		if (input[i[0]] == '\'' || input[i[0]] == '\"')
		{
			if (!process_quotes(input, &ret, i))
				return (exit_error_char(1, NULL, data));
		}
		else
			handle_spaces(input, &ret, i);
	}
	ret[i[1]] = '\0';
	return (ret);
}
