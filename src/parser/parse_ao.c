/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:37:40 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/01 11:57:00 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

void	ao_parenthesis_error(int paren, int *error)
{
	if (paren != 0)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
	}
}

int	operand_error(int i, t_token *dup, int *error)
{
	if (i == 0 || !dup->next || dup->next->type == PIPE || dup->next->type
		== AND || dup->next->type == OR)
	{
		printf(SYNTAX_ERROR);
		*error = 2;
		return (-1);
	}
	return (i);
}

int	ao_location(t_token *tokens, int *error)
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
		if ((dup->type == AND || dup->type == OR) && paren == 0)
		{
			i = operand_error(i, dup, error);
			return (i);
		}
		i++;
		dup = dup->next;
	}
	ao_parenthesis_error(paren, error);
	return (-1);
}

void	ao_type_setter(t_token *token, t_NodeAST *node, int operand)
{
	int		i;
	t_token	*dup;

	i = 0;
	dup = token;
	while (i < operand + 1)
	{
		if (dup->type == AND)
			node->type = NODE_AND;
		if (dup->type == OR)
			node->type = NODE_OR;
		dup = dup->next;
		i++;
	}
}

t_NodeAST	*set_ao_node(t_token *token, int *error)
{
	t_NodeAST	*node;
	t_token		*left;
	t_token		*dup;
	int			operand;

	operand = ao_location(token, error);
	if (operand == -1)
		return (NULL);
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	dup = token;
	left = token;
	ao_type_setter(dup, node, operand);
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
