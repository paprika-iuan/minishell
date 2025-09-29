/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:35:22 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/29 15:04:39 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	pipe_location(t_token *tokens)
{
	int		i;
	int		paren;
	t_token	*dup;

	i = 0;
	paren = 0;
	dup = tokens;
	while (dup)
	{
		if (dup->content[0] == '(')
			paren++;
		else if (dup->content[0] == ')')
			paren--;
		else if (dup->type == PIPE && paren == 0)
			return (i);
		i++;
		dup = dup->next;
	}
	return (-1);
}

t_NodeAST	*set_pipe_node(t_token *token)
{
	t_NodeAST	*node;
	t_token		*left;
	t_token		*dup;
	int			operand;

	operand = pipe_location(token);
	if (operand == -1)
		return (NULL);
	left = token;
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	dup = token;
	node->type = NODE_PIPE;
	left = set_reparse(dup, operand);
	node->binary.left = parse_ast(left);
	if (!node->binary.left)
		return (NULL);
	free_token_list(left);
	dup = consume_tokens(dup, operand);
	if (!dup->content)
		return (NULL);
	node->binary.right = parse_ast(dup);
	if (!node->binary.right)
		return (NULL);
	return (node);
}
