/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:50:03 by hchreif           #+#    #+#             */
/*   Updated: 2024/12/31 18:33:19 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_worddup(char const *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*ft_free_all(char **words, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

void	*helper(char **words, char *s, char c)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			while (s[i] && s[i] == c && s[i + 1] == c)
				i++;
			words[j++] = ft_worddup(s, start, i);
			if (!words[j - 1])
				return (ft_free_all(words, j - 1));
		}
		if (s[i])
			i++;
	}
	words[j] = NULL;
	return ("SUCCESS");
}

char	**ft_split_3(char *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (ft_wordcount(s, c) == 1)
	{
		words[0] = ft_strdup((const char *)s);
		words[1] = NULL;
		return (words);
	}
	if (!words)
		return (NULL);
	if (helper(words, s, c) == NULL)
		return (NULL);
	return (words);
}
