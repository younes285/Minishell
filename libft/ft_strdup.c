/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:31:15 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 13:38:31 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s)
{
	size_t	c;

	c = 0;
	while (*(s + c))
		c++;
	return (c);
}

char	*ft_strdup(char const *str)
{
	char	*s;
	int		c;

	c = 0;
	s = (char *)malloc(ft_len(str) + 1);
	if (!s)
		return (NULL);
	while (*(str + c))
	{
		*(s + c) = *(str + c);
		c++;
	}
	*(s + c) = '\0';
	return (s);
}		
