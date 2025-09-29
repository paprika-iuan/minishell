/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:55:02 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/26 17:25:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT_APP ||
			type == REDIR_OUT_TRUNC || type == REDIR_HEREDOC);
}

int	find_redir(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (is_redirection(token->type))
		{
			if (is_redirection(token->next->type))
			{
				//set_error(syntax error)
				exit (1);
			}
		return (i);
		}
		token = token->next;
		i++;
	}
	return (0);
}

t_NodeAST	*set_redirect_node(t_token *tokens)
{
	t_NodeAST	*node;
	int			red_pos;

	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_REDIRECT;
	red_pos = find_redir(tokens);
	if (!red_pos)
		return (NULL);
	tokens = consume_tokens(tokens, red_pos - 1);
	node->redirect.type = tokens->type;
	if (!tokens->next->content)
	{
		//set_error(syntax error near unexpected token 'newline');
		return (NULL);
	}
	node->redirect.file = tokens->next->content;
	node->redirect.fd = -1;
	node->redirect.redirect = set_redirect_node(tokens->next->next);
	return (node);
}
