/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:59:55 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 16:48:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	subshell_child_process(t_NodeAST *node, t_env **env_ref)
{
	int			result;
	t_NodeAST	*reparse;

	if (!do_redirections(node->subshell.redirect, *env_ref))
		exit(ERROR);
	reparse = node->subshell.reparse;
	if (reparse->type == NODE_CMD)
		result = execute_one_command(reparse, env_ref);
	else
		result = execute_ast(reparse, env_ref);
	free_ast(node->subshell.reparse);
	exit(result);
}

int	execute_subshell(t_NodeAST *node, t_env *env)
{
	pid_t		pid;
	int			status;
	int			exit_code;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FORK_FAILED);
	if (pid == 0)
		subshell_child_process(node, &env);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), WAITPID_FAILED);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = ERROR;
	return (exit_code);
}

int	execute_ast(t_NodeAST *node, t_env **env_ref)
{
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_and_or(node, env_ref));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_sequence(node, *env_ref));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, *env_ref));
	else
		return (execute_command(node, env_ref));
}
