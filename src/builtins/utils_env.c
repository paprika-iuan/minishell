/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:19:07 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/23 15:34:37 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}

t_env	*last_env_node(t_env *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	add_to_env_list(t_env *env, t_env *new_node)
{
	if (!new_node)
		return ;
	if (!env)
		env = new_node;
	else
		last_env_node(env)->next = new_node;
}

t_env	*create_env_node(char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	if (!new_node->content)
	{
		printf("aa\n");
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
