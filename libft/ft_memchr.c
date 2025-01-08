/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:45:18 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 11:45:35 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int ch, size_t n)
{
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *) s;
	c = (unsigned char) ch;
	while (n != 0)
	{
		if (*str == c)
			return ((void *)str);
		str ++;
		n --;
	}
	return (NULL);
}
