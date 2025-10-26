/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:26:31 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 16:47:12 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	execute_and_or_binary(t_NodeAST *node, t_mini *mini)
{
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_and_or(node, mini));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_sequence(node, mini));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, mini));
	else
		return (execute_one_command(node, mini));
}

t_NodeAST	*find_or_in_right_chain(t_NodeAST *node)
{
	if (!node)
		return (NULL);
	if (node->type == NODE_OR)
		return (node);
	if (node->type == NODE_AND)
		return (find_or_in_right_chain(node->binary.right));
	return (NULL);
}

t_NodeAST	*find_and_in_right_chain(t_NodeAST *node)
{
	if (!node)
		return (NULL);
	if (node->type == NODE_AND)
		return (node);
	if (node->type == NODE_OR)
		return (find_or_in_right_chain(node->binary.right));
	return (NULL);
}

int	execute_and_or(t_NodeAST *node, t_mini *mini)
{
	int			result_left;
	t_NodeAST	*or;
	t_NodeAST	*and;

	result_left = execute_and_or_binary(node->binary.left, mini);
	or = find_or_in_right_chain(node->binary.right);
	and = find_and_in_right_chain(node->binary.right);
	if (node->type == NODE_AND && result_left != 0 && or)
		return (execute_ast(or->binary.right, mini));
	if (node->type == NODE_AND && result_left == 0)
		return (execute_and_or_binary(node->binary.right, mini));
	if (node->type == NODE_OR && result_left == 0 && and)
		return (execute_and_or_binary(and->binary.right, mini));
	if (node->type == NODE_OR && result_left != 0)
		return (execute_and_or_binary(node->binary.right, mini));
	return (result_left);
}
