/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:13:24 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/29 12:04:46 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_lstlast_parse(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_parse(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_parse(*lst);
	tmp->next = new;
}

t_token	*ft_lst_node_cpy(t_token *cpy_from)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strndup(cpy_from->content, ft_strlen(cpy_from->content));
	new->type = cpy_from->type;
	new->next = NULL;
	return (new);
}

t_token	*consume_tokens(t_token *token, int moves)
{
	int	i;

	i = 0;
	while (token && i < moves + 1)
	{
		token = token->next;
		i++;
	}
	return (token);
}
