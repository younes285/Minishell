/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:13:31 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 12:02:46 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s, char const *f_s, size_t n)
{
	size_t	j;
	char	*str;
	char	*f_str;

	str = (char *) s;
	f_str = (char *) f_s;
	if (!str && !n)
		return (NULL);
	if (!*f_str)
		return (str);
	while (*str && n--)
	{
		j = 0;
		while (*(str + j) == *(f_str + j)
			&& *(f_str + j) && j <= n)
		{
			if (!*(f_str + j + 1))
				return (str);
			j++;
		}
		str++;
	}
	return (NULL);
}
