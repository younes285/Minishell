/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:53:16 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/16 14:12:58 by hchreif          ###   ########.fr       */
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

static int	check(char const *s, char c)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			r ++;
		i++;
	}
	return (r);
}

static int	sub_len(char const *s, char d)
{
	int	i;
	int	j;
	int	c;

	if (!s || !(*s))
		return (0);
	i = 0;
	j = ft_len(s) - 1;
	c = 0;
	while (s[i] == d)
		i++;
	while (s[j] == d)
		j--;
	while (i <= j)
	{
		if (i < ft_len(s) && s[i] == d && s[i + 1] != d)
			c++;
		i++;
	}
	if (check(s, d) != ft_len(s))
		c++;
	return (c);
}

static char	*fts_substr(char const *s, unsigned int start, size_t len)
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

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		i;
	int		l;
	int		ch;

	if (!s)
		return (NULL);
	ch = 0;
	a = (char **)malloc(sizeof(char *) * (sub_len(s, c) + 1));
	if (!a)
		return (NULL);
	i = -1;
	l = 0;
	while (i++, ch < sub_len(s, c))
	{
		if ((s[i] == c || s[i] == '\0') && l != 0)
		{
			a[ch++] = fts_substr(s, i - l, l);
			l = 0;
		}
		else if (s[i] != c)
			l++;
	}
	a[ch] = NULL;
	return (a);
}
