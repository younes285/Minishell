/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:00:35 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 13:12:39 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t s)
{
	void	*to_return;
	int		size;
	int		i;

	size = 1;
	i = 0;
	if (num && s)
	{
		size = num * s;
		if (num != size / s)
			return (NULL);
	}
	to_return = malloc(size);
	if (!to_return)
		return (NULL);
	while (size > 0)
	{
		*((char *)to_return + i) = 0;
		i ++;
		size --;
	}
	return (to_return);
}
