/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:26:31 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/05 13:26:33 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	execute_and_or_binary(t_NodeAST *node, t_env *env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_and_or(node, env));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_sequence(node, env));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, env));
	else
		return (execute_one_command(node, env));
}

int	execute_and_or(t_NodeAST *node, t_env *env)
{
	int	result_left;

	result_left = execute_and_or_binary(node->binary.left, env);
	if (node->type == NODE_AND && result_left == 0)
		return (execute_and_or_binary(node->binary.right, env));
	if (node->type == NODE_OR && result_left != 0)
		return (execute_and_or_binary(node->binary.right, env));
	return (result_left);
}
