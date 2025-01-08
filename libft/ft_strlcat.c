/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:48:12 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/14 13:04:45 by hchreif          ###   ########.fr       */
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

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		dest_len;
	size_t		total_len;
	const char	*s;

	if ((!dest || !src) && !n)
		return (0);
	s = src;
	dest_len = 0;
	while (*(dest + dest_len) && dest_len < n)
		dest_len++;
	if (dest_len < n)
		total_len = dest_len + ft_len(s);
	else
		return (n + ft_len(s));
	while (*s && (dest_len + 1) < n)
	{
		*(dest + dest_len) = *s++;
		dest_len++;
	}
	*(dest + dest_len) = '\0';
	return (total_len);
}
