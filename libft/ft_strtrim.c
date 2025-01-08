/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:55:37 by hchreif           #+#    #+#             */
/*   Updated: 2024/08/22 16:37:09 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

static int	check_in(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tr;
	int		r;
	int		l;
	int		i;

	if (!s1 || !set)
		return (NULL);
	r = 0;
	l = ft_len(s1) - 1;
	while (check_in(set, s1[r]) == 1 && s1[r])
		r ++;
	while (check_in(set, s1[l]) == 1 && l >= r)
		l --;
	tr = (char *)malloc(sizeof(char) * (l - r + 2));
	if (!tr)
		return (NULL);
	i = 0;
	while (r <= l)
	{
		tr[i] = s1[r];
		r++;
		i++;
	}
	tr[i] = '\0';
	return (tr);
}
