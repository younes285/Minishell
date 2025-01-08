/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:18:46 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:32:52 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i ++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i ++;
	}
	return (dest);
}

int	is_delimiter(char c, char delimiter)
{
	return (c == delimiter);
}

void	toggle_quote(int *in_quotes, char *quote_char, char current_char)
{
	if (*in_quotes == 0)
	{
		*in_quotes = 1;
		*quote_char = current_char;
	}
	else if (current_char == *quote_char)
	{
		*in_quotes = 0;
	}
}
