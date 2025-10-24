/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:10 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 10:51:14 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	del_env_value(char *env_content, t_env *env)
{
	t_env	*current;
	t_env	*prev;
	int		len;

	current = env;
	prev = NULL;
	len = ft_strlen(env_content);
	while (current)
	{
		if (!ft_strncmp(env_content, current->content, len) && (
				current->content[len] == '=' || current->content[len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env *env)
{
	int	i;

	if (!args || !env || !env->content
		|| (ft_isnumeric(env->content) && !env->next))
		return (ERROR);
	i = 0;
	while (args[i])
	{
		del_env_value(args[i], env);
		i++;
	}
	return (0);
}
