/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:16:24 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/13 12:51:11 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_num(int n)
{
	if (n >= 48 && n <= 57)
		return (1);
	return (0);
}

static int	ch_sp(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int	ft_atoi(const char *num)
{
	int	n;
	int	s;

	s = 1;
	n = 0;
	while (*num && ch_sp(*num) == 1)
		num++;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			s = -1;
		num ++;
	}
	while (*num && is_num (*num))
	{
		n = n * 10 + (*num - 48);
		num ++;
	}
	return (s * n);
}
