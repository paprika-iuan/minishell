/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:35:22 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/01 11:56:55 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	is_right_empty(t_token *dup, int *error)
{
	if (!dup && !dup->content)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
		return (1);
	}
	return (0);
}

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
			i = operand_error(i, dup, error);
			return (i);
		}
		i++;
		dup = dup->next;
	}
	return (-1);
}

void	free_left_set_right(t_token *left, t_token **dup, int operand)
{
	free_token_list(left);
	*dup = consume_tokens(*dup, operand);
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
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	dup = token;
	left = token;
	node->type = NODE_PIPE;
	left = set_reparse(dup, operand, error);
	node->binary.left = parse_ast(left, error);
	if (!node->binary.left || *error != 0)
		return (NULL);
	free_left_set_right(left, &dup, operand);
	if (is_right_empty(dup, error))
		return (NULL);
	node->binary.right = parse_ast(dup, error);
	if (!node->binary.right)
		return (NULL);
	return (node);
}
