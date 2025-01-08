/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:56:12 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/15 11:46:27 by hchreif          ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	holder;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_len(s))
		len = 0;
	else if (len > ft_len(s) - start)
		len = ft_len(s) - start;
	p = (char *)malloc(sizeof(char) * (len + 1));
	holder = len;
	if (!p)
		return (NULL);
	*(p + len) = '\0';
	while (len > 0 && *(s + start))
	{
		*(p++) = *(s + start);
		start ++;
		len --;
	}
	return (p - holder);
}
