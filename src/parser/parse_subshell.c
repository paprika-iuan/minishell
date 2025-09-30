/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:31:11 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/30 16:17:06 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	parenthesis_close(t_token *tokens)
{
	int		i;
	int		count; 
	t_token	*dup;

	i = 0;
	count = 0;
	dup = tokens;
	if (dup->content[0] == '(')
	{
		while (dup)
		{
			if (dup->content[0] == '(')
				count++;
			else if (dup->content[0] == ')')
			{
				count--;
				if (count == 0)
					return (i);
			}
			i++;
			dup = dup->next;
		}
	}
	return (-1);
}

t_token	*set_reparse(t_token *tokens, int close, int *error)
{
	int		i;
	t_token	*head;
	t_token	*dup;
	t_token	*reparse;

	i = 0;
	dup = tokens;
	head = NULL;
	while (dup && i < close)
	{
		reparse = ft_lst_node_cpy(dup);
		ft_lstadd_back_parse(&head, reparse);
		dup = dup->next;
		i++;
	}
	if (!head)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
	}
	return (head);
}

t_NodeAST	*set_subshell_node(t_token *tokens, int *error)
{
	t_NodeAST	*node;
	t_NodeAST	*redir;
	t_token		*reparse;
	t_token		*dup;
	int			close;


	close = parenthesis_close(tokens);
	if (close == -1)
		return (NULL);
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	reparse = set_reparse(tokens->next, close - 1, error);
	node->subshell.reparse = parse_ast(reparse, error);
	free_token_list(reparse);
	dup = consume_tokens(tokens, close - 1);
	if (dup->next->type == SUBSHELL)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
		return (NULL);
	}
	redir = set_redirect_node(dup, error);
	node->subshell.redirect = redir;
	return (node);
}
