/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:55:02 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/01 11:47:22 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT_APP || type
		== REDIR_OUT_TRUNC || type == REDIR_HEREDOC);
}

int	find_redir(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (is_redirection(token->type))
			return (i);
		token = token->next;
		i++;
	}
	return (-1);
}

int	next_is_file(t_token *tokens, int *error)
{
	if (!tokens->next || !tokens->next->content || tokens->next->type != WORD)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
		return (1);
	}
	return (0);
}

static char	*dup_redir_file(t_token *token, int *error)
{
	char	*redir;

	if (!token || !token->content)
	{
		*error = 1;
		return (NULL);
	}
	redir = ft_strndup(token->content, ft_strlen(token->content));
	if (!redir)
	{
		*error = 1;
		return (NULL);
	}
	return (redir);
}

t_NodeAST	*set_redirect_node(t_token *tokens, int *error)
{
	t_NodeAST	*node;
	int			red_pos;

	if (*error != 0)
		return (NULL);
	red_pos = find_redir(tokens);
	if (red_pos < 0)
		return (NULL);
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_REDIRECT;
	tokens = consume_tokens(tokens, red_pos - 1);
	node->redirect.type = tokens->type;
	if (next_is_file(tokens, error))
		return (free(node), NULL);
	node->redirect.file = dup_redir_file(tokens->next, error);
	if (!node->redirect.file)
		return (NULL);
	if (is_subshell(tokens->next, error))
		return (NULL);
	node->redirect.fd = -1;
	node->redirect.redirect = set_redirect_node(tokens->next->next, error);
	return (node);
}
// t_NodeAST	*set_redirect_node(t_token *tokens, int *error)
// {
// 	t_NodeAST	*node;
// 	char		*redir;
// 	int			red_pos;

// 	if (*error != 0)
// 		return (NULL);
// 	red_pos = find_redir(tokens);
// 	if (red_pos < 0)
// 		return (NULL);
// 	node = malloc(sizeof(t_NodeAST));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_REDIRECT;
// 	tokens = consume_tokens(tokens, red_pos - 1);
// 	node->redirect.type = tokens->type;
// 	if (next_is_file(tokens, error))
// 		return (NULL);
// 	redir = ft_strndup(tokens->next->content, ft_strlen(tokens->next->content));
// 	if (!redir)
// 		return (NULL);
// 	node->redirect.file = redir;
// 	if (is_subshell(tokens->next, error))
// 		return (NULL);
// 	node->redirect.fd = -1;
// 	node->redirect.redirect = set_redirect_node(tokens->next->next, error);
// 	return (node);
// }
