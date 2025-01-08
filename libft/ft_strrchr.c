/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:45:55 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 11:45:56 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	ch;
	char	*to_return;

	str = (char *) s;
	ch = (char) c;
	to_return = NULL;
	while (*str)
	{
		if (*str == ch)
			to_return = str;
		str++;
	}
	if (ch == '\0')
		return (str);
	return (to_return);
}
