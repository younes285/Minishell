/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:36:06 by moyounes          #+#    #+#             */
/*   Updated: 2025/01/03 19:48:30 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_ok(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	is_ok2(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '_' || c == '=' || c == ':' || c == '!')
		return (1);
	else
		return (0);
}

char	*add_equal(char *str)
{
	char	*temp;

	temp = malloc(ft_strlen(str) + 2);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, str);
	temp[ft_strlen(str)] = '=';
	temp[ft_strlen(str) + 1] = '\0';
	return (temp);
}

char	*env_search(char *str, char **env)
{
	char	*tos;
	int		i;

	tos = add_equal(str);
	i = 0;
	if (!tos)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], tos, ft_strlen(tos)) == 0)
		{
			free(tos);
			return (env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	free(tos);
	return (NULL);
}

void	edit_str(char **str, int start, int end, char *env_value)
{
	int		new_len;
	char	*new_str;

	if (env_value != NULL)
		new_len = start + ft_strlen(env_value) + ft_strlen(*str + end);
	else
		new_len = start + ft_strlen(*str + end);
	new_str = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return ;
	ft_strncpy(new_str, *str, start);
	new_str[start] = '\0';
	if (env_value != NULL)
		ft_strcat(new_str, env_value);
	ft_strcat(new_str, *str + end);
	free(*str);
	*str = ft_strdup(new_str);
	printf("from edit str : |%s|\n", *str);
	free(new_str);
	new_str = NULL;
}
