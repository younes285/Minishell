/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:54:02 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/16 12:30:06 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num(int n)
{
	int	l;

	l = 1;
	if (n < 0)
	{
		l++;
		n = n * (-1);
	}
	while (n / 10 > 0)
	{
		l++;
		n = n / 10;
	}
	return (l);
}

static char	*min_n(char *s)
{
	char	*d;
	int		i;

	d = "-2147483648";
	i = 0;
	while (i < 11)
	{
		s[i] = d[i];
		i++;
	}
	s[11] = '\0';
	return (s);
}

static void	fill(char *ret, int l, int f, int n)
{
	while (l--, l >= f)
	{
		ret[l] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		l;
	int		f;

	if (n == -2147483648)
	{
		ret = (char *)malloc(sizeof(char) * 12);
		return (min_n(ret));
	}
	l = num(n);
	f = 0;
	if (n < 0)
	{
		f = 1;
		n = n * (-1);
	}
	ret = (char *)malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	ret[l] = '\0';
	if (f == 1)
		ret[0] = '-';
	fill(ret, l, f, n);
	return (ret);
}
