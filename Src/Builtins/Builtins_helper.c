/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moyounes <moyounes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:01:43 by moyounes          #+#    #+#             */
/*   Updated: 2024/09/14 13:47:13 by moyounes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	env_helper(char **copied_env, int i, int j, t_data *data)
{
	if (!copied_env || i < 0 || j < 0)
	{
		exit_status_helper("env_helper: Invalid arguments", 1, data);
		return (-1);
	}
	printf("declare -x ");
	while (copied_env[i][j] != '=' && copied_env[i][j] != '\0')
	{
		printf("%c", copied_env[i][j]);
		j++;
	}
	j++;
	return (j);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_ptr;

	if (!dest || !src)
		return (NULL);
	dest_ptr = dest;
	while (*src != '\0')
	{
		*dest_ptr++ = *src++;
	}
	*dest_ptr = '\0';
	return (dest);
}

char	*get_path(const char *cmd, char **envp, t_data *data)
{
	char	*value;
	int		len;
	int		i;

	if (!cmd || !envp)
	{
		exit_status_helper("get_path: Null pointer", 1, data);
		return (NULL);
	}
	value = NULL;
	len = ft_strlen(cmd);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, len) == 0 && envp[i][len] == '=')
		{
			value = ft_strdup(envp[i] + len + 1);
			break ;
		}
		i++;
	}
	return (value);
}
