/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:59:10 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/14 13:03:30 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, char const *s, size_t n)
{
	size_t	i;
	size_t	c;
	char	*src;

	src = (char *) s;
	i = ft_len(src);
	if (n > 0)
	{
		if (i >= n)
			c = n -1;
		else
			c = i;
		while (c != 0 && *src)
		{
			*dest++ = *src++;
			c --;
		}
		*dest = '\0';
	}
	return (i);
}
