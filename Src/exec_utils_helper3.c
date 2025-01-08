/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_helper3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:05:28 by moyounes          #+#    #+#             */
/*   Updated: 2024/12/31 18:32:19 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	check_s_equal(char *s, char *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s || !d || !(*s) || !(*d))
		return (0);
	while (s[i])
	{
		if (s[i] != d[j] || (i + 1 == (int)ft_strlen(s)
				&& j + 1 != (int)ft_strlen(d)))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end)
	{
		dest_end++;
	}
	while (*src)
	{
		*dest_end++ = *src++;
	}
	*dest_end = '\0';
	return (dest);
}

char	*rejoin_args(char **args, t_data *data)
{
	int		i;
	char	*result;
	char	*temp;
	size_t	result_len;

	if (!args || !args[0])
		return (NULL);
	result = strdup(args[0]);
	if (!result)
		return (exit_error_char(1, NULL, data));
	i = 1;
	while (args[i])
	{
		result_len = strlen(result) + strlen(args[i]) + 2;
		temp = malloc(result_len);
		ft_strcpy(temp, result);
		ft_strcat(temp, " ");
		ft_strcat(temp, args[i]);
		free(result);
		result = temp;
		i++;
	}
	return (result);
}
