/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:35:22 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/30 15:11:33 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	pipe_location(t_token *tokens, int *error)
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
		{
			if (i == 0 || !dup->next || dup->next->type == PIPE || dup->next->type == AND || dup->next->type == OR)
			{
				printf(SYNTAX_ERROR);
				*error = 2;
				return (-1);
			}
			return (i);
		}
		i++;
		dup = dup->next;
	}
	return (-1);
}

t_NodeAST	*set_pipe_node(t_token *token, int *error)
{
	t_NodeAST	*node;
	t_token		*left;
	t_token		*dup;
	int			operand;

	operand = pipe_location(token, error);
	if (operand == -1)
		return (NULL);
	left = token;
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	dup = token;
	node->type = NODE_PIPE;
	left = set_reparse(dup, operand, error);
	node->binary.left = parse_ast(left, error);
	if (!node->binary.left || *error != 0)
		return (NULL);
	free_token_list(left);
	dup = consume_tokens(dup, operand);
	if (!dup || !dup->content)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
		return (NULL);
	}
	node->binary.right = parse_ast(dup, error);
	if (!node->binary.right)
		return (NULL);
	return (node);
}
