/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:19:07 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/15 17:42:51 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	basic_err(char *x)
{
	if (!x)
		exit (NULL);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back(t_env **lst, t_env *newnode)
{
	if (newnode == NULL)
		return ;
	if (*lst == NULL)
		*lst = newnode;
	else
		ft_lstlast(*lst)->next = newnode;
}

t_env	*ft_lstnew(void *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
