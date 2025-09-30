/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:43:54 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/30 12:43:56 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int count_pipes(t_NodeAST *node)
{
	int count;

	count = 0;
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		count = 1;
	if (node->type == NODE_AND || node->type == NODE_OR || node->type == NODE_PIPE)
	{
		count += count_pipes(node->binary.left);
		count += count_pipes(node->binary.right);
	}
	else if (node->type == NODE_SUBSHELL)
		count += count_pipes(node->subshell.reparse);
	return (count);
}

void	set_pipes()
{
	int count_pipes(t_NodeAST *node);
}
