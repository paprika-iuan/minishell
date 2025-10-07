/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:59:55 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/01 15:59:56 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	execute_subshell(t_NodeAST *node, t_env *env)
{
	int		result;
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FORK_FAILED);
	if (pid == 0)
	{
		result = execute_ast(node->subshell.reparse, env);
		exit(result);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), WAITPID_FAILED);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = ERROR;
	return (exit_code);
}

int	execute_ast(t_NodeAST *node, t_env *env)
{
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_and_or(node, env));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_sequence(node, env));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, env));
	else
		return (execute_command(node, env));
}
