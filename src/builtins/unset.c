/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:10 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/24 16:11:24 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*get_list_at_key(t_env *current, char *key)
{
	int		len;

	len = ft_strlen(key);
	while (current)
	{
		if (!ft_strncmp(key, current->content, len) && (
				current->content[len] == '=' || current->content[len] == '\0'))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_env	*get_list_at_prev2key(t_env *current, char *key)
{
	int		len;
	t_env	*prev;

	prev = NULL;
	len = ft_strlen(key);
	while (current)
	{
		if (!ft_strncmp(key, current->content, len) && (
				current->content[len] == '=' || current->content[len] == '\0'))
			return (prev);
		prev = current;
		current = current->next;
	}
	return (NULL);
}

void	del_env_value(char *env_content, t_env **env_ref)
{
	t_env	*current;
	t_env	*prev;
	t_env	*env;
	
	env = *env_ref;
	current = get_list_at_key(env, env_content);
	if (!current)
		return ;
	prev = get_list_at_prev2key(env, env_content);
	if (prev == NULL)
	{
		*env_ref = current->next;
		free(current->content);
		free(current);
		return ;
	}
	prev = current->next;
	free(current->content);
	free(current);
}

int	ft_unset(char **args, t_env **env_ref)
{
	int		i;
	t_env	*env;

	env = *env_ref;
	if (!args || !env || !env->content
		|| (ft_isnumeric(env->content) && !env->next))
		return (ERROR);
	i = 0;
	while (args[i])
	{
		del_env_value(args[i], env_ref);
		i++;
	}
	return (0);
}
