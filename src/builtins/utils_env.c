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

t_env	*envcpy(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	if (!*envp)
		return (NULL);
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
			return (free_env_list(head), NULL);
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		i++;
	}
	return (head);
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
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
