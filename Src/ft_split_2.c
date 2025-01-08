/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:53:16 by hchreif           #+#    #+#             */
/*   Updated: 2025/01/02 11:43:38 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	count_segments(const char *s, char c)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;

	count = 1;
	i = 0;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			toggle_quote(&in_quotes, &quote_char, s[i]);
		else if (is_delimiter(s[i], c) && !in_quotes)
			count++;
		i++;
	}
	return (count);
}

static char	*allocate_segment(const char *s, int start, int end)
{
	char	*segment;
	int		len;

	len = end - start;
	segment = (char *)malloc(len + 1);
	if (!segment)
		return (NULL);
	ft_strlcpy(segment, s + start, len + 1);
	return (segment);
}

static void	free_segments(char **segments, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(segments[i]);
		i++;
	}
	free(segments);
}

static int	process_segment(char **segments, const char *s, char c, int *index)
{
	int		start;
	int		in_quotes;
	char	quote_char;

	start = *index;
	in_quotes = 0;
	while (s[*index] && (!is_delimiter(s[*index], c) || in_quotes))
	{
		if (s[*index] == '\'' || s[*index] == '\"')
			toggle_quote(&in_quotes, &quote_char, s[*index]);
		(*index)++;
	}
	*segments = allocate_segment(s, start, *index);
	return (*segments != NULL);
}

char	**ft_split_2(char *s, char c)
{
	char	**segments;
	int		seg_count;
	int		i[2];

	if (!s)
		return (NULL);
	seg_count = count_segments(s, c);
	segments = (char **)malloc(sizeof(char *) * (seg_count + 1));
	if (!segments)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (i[1] < seg_count)
	{
		while (is_delimiter(s[i[0]], c))
			i[0]++;
		if (!process_segment(&segments[i[1]], s, c, &i[0]))
		{
			free_segments(segments, i[1]);
			return (NULL);
		}
		i[1]++;
	}
	segments[i[1]] = NULL;
	return (segments);
}
