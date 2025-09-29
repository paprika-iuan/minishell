/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:37:40 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/29 15:04:32 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	ao_location(t_token *tokens)
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
			return (i);
		i++;
		dup = dup->next;
	}
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

t_NodeAST	*set_ao_node(t_token *token)
{
	t_NodeAST	*node;
	t_token		*left;
	t_token		*dup;
	int			operand;

	operand = ao_location(token);
	if (operand == -1)
		return (NULL); //parse error near operand.
	left = token;
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	dup = token;
	ao_type_setter(dup, node, operand);
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
