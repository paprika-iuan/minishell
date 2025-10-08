/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:50:04 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 10:40:50 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	int		key_len;
	t_env	*iter;
	char	*eq;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	iter = env;
	while (iter)
	{
		eq = ft_strchr(iter->content, '=');
		if ((eq - iter->content) == key_len
			&& ft_strncmp(key, iter->content, key_len) == 0)
			return (eq + 1);
		iter = iter->next;
	}
	return (NULL);
}

static char	*build_env_content(const char *key, const char *value)
{
	size_t	key_len;
	size_t	value_len;
	char	*result;

	if (!key || !value)
		return (NULL);
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	result = malloc(key_len + 1 + value_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, key, key_len);
	result[key_len] = '=';
	ft_memcpy(result + key_len + 1, value, value_len);
	result[key_len + 1 + value_len] = '\0';
	return (result);
}

int	set_env_value(char *key, char *value, t_env *env)
{
	t_env	*iter;
	char	*eq;
	char	*new_content;
	int		key_len;

	if (!key || !value || !env)
		return (-1);
	key_len = ft_strlen(key);
	iter = env;
	while (iter)
	{
		eq = ft_strchr(iter->content, '=');
		if (eq && eq - iter->content == key_len
			&& ft_strncmp(key, iter->content, key_len) == 0)
		{
			new_content = build_env_content(key, value);
			if (!new_content)
				return (-1);
			free(iter->content);
			iter->content = new_content;
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

int	ft_env(t_env *cp_env)
{
	if (!cp_env || cp_env->content)
		return (1);
	while (cp_env)
	{
		if (ft_strchr(cp_env->content, '='))
			printf("%s\n", cp_env->content);
		cp_env = cp_env->next;
	}
	return (0);
}
