/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:41:30 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 10:30:57 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*envcpy(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	node = NULL;
	basic_err(*envp);
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->content = ft_strdup(envp[i]);
		node->next = NULL;
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		i++;
	}
	return (head);
}
