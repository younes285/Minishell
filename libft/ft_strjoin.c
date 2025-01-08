/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:41:56 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/14 13:54:41 by hchreif          ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const*s2)
{
	char	*s;
	int		t;

	if (!s1 || !s2)
		return (NULL);
	t = ft_len(s1) + ft_len(s2);
	s = (char *)malloc(sizeof(char) * (t + 1));
	if (!s)
		return (NULL);
	while (*s1)
		*(s++) = *(s1++);
	while (*s2)
		*(s++) = *(s2++);
	*s = '\0';
	return (s - t);
}
