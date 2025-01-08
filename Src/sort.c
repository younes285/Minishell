/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:45:54 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/08 22:44:34 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**bubble_sort(char **arr, int n)
{
	int		i;
	int		j;
	char	**sorted_arr;

	sorted_arr = malloc((n + 1) * sizeof(char *));
	if (!sorted_arr)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < n)
		sorted_arr[i] = ft_strdup((const char *)arr[i]);
	sorted_arr[n] = NULL;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(sorted_arr[j], sorted_arr[j + 1]) > 0)
				swap(&sorted_arr[j], &sorted_arr[j + 1]);
			j++;
		}
		i++;
	}
	free_arr(arr);
	return (sorted_arr);
}

int countWords(const char *str) {
    int count = 0;
    int inWord = 0;
	int i = 0;

    if (str == NULL) {
        return 0;
    }

    while (*(str + i)) {
        if (*(str + i) == ' ' || *(str + i) == '\t') {
            inWord = 0; 
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
        i++;
    }

    return count;
}

int	notInQuotes(char *str, char *toFind)
{
	int		i[2];
	int		IQuotes[2];
	char	quote = 'a';
	char	*s;

	IQuotes[0] = -1;
	IQuotes[1] = -1;
	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '\"' || str[i[0]] == '\'')
		{
			IQuotes[0] = i[0];
			quote = str[i[0]];
			i[0]++;
			break;
		}
		i[0]++;
	}
	if (quote != 'a')
	{	
		while (str[i[0]] != quote)
			i[0]++;
		IQuotes[1] = i[0];
	}
	s = ft_strstr(str, toFind);
	while (*(s + i[1]) != '\0')
		i[1]++;
	if (i[1] > (int)ft_strlen(str) - IQuotes[1] && i[1] < (int)ft_strlen(str) - IQuotes[0])
		return (0);
	return (1);
}