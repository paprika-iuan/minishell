/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:27:29 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/07 15:27:31 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

void	init_pipe_struct(t_pipe_struct *t_pipe)
{
	t_pipe->num_pipes = 0;
	t_pipe->pipes = NULL;
	t_pipe->pipe_idx = -1;
	t_pipe->pid = -1;
	t_pipe->child_pids = NULL;
}

t_NodeAST	*get_current_cmd(t_NodeAST *node, int pipe_idx)
{
	int			i;
	t_NodeAST	*curr_node;

	if (pipe_idx == 0)
		return (node->binary.left);
	i = 0;
	curr_node = node;
	while (i < pipe_idx)
	{
		curr_node = curr_node->binary.right;
		i++;
	}
	return (curr_node);
}

void	setup_cmd_fds(t_pipe_struct *t_pipe)
{
	// MISSING REDIRECTS
	if (t_pipe->pipe_idx == 0 && t_pipe->num_pipes > 0)
	{
		dup2(t_pipe->pipes[1], STDOUT_FILENO);
	}
	else if (t_pipe->pipe_idx == t_pipe->num_pipes)
	{
		dup2(t_pipe->pipes[2 * (t_pipe->pipe_idx - 1)], STDIN_FILENO);
	}
	else
	{
		dup2(t_pipe->pipes[2 * (t_pipe->pipe_idx - 1)], STDIN_FILENO);
		dup2(t_pipe->pipes[2 * t_pipe->pipe_idx + 1], STDOUT_FILENO);
	}
}

int	fork_child(t_NodeAST *node, t_pipe_struct *t_pipe, t_env *env)
{
	t_NodeAST	*current_cmd;

	t_pipe->pid = fork();
	if (t_pipe->pid < 0)
		return (perror("fork"), FORK_FAILED);
	t_pipe->child_pids[t_pipe->pipe_idx] = t_pipe->pid;
	if (t_pipe->pid == 0)
	{
		// do_redirections(node);
		setup_cmd_fds(t_pipe);
		close_pipes(t_pipe);
		current_cmd = get_current_cmd(node, t_pipe->pipe_idx);
		exit(execute_ast(current_cmd, env));
	}
	return (FORK_SUCCESS);
}

int	execute_pipe_sequence(t_NodeAST *node, t_env *env)
{
	t_pipe_struct	t_pipe;
	pid_t			last_pid;
	int				last_cmd_status;

	init_pipe_struct(&t_pipe);
	if (!set_pipes(&t_pipe, node))
		return (MALLOC_FAILED);
	if (!allocate_child_pids(&t_pipe))
		return (close_pipes(&t_pipe), MALLOC_FAILED);
	while (t_pipe.pipe_idx < t_pipe.num_pipes + 1)
	{
		last_cmd_status = fork_child(node, &t_pipe, env);
		if (last_cmd_status == FORK_FAILED)
		{
			close_pipes(&t_pipe);
			free(t_pipe.child_pids);
			return (FORK_FAILED);
		}
		t_pipe.pipe_idx++;
	}
	close_pipes(&t_pipe);
	last_pid = t_pipe.child_pids[t_pipe.num_pipes];
	last_cmd_status = wait_for_children(&t_pipe);
	free(t_pipe.child_pids);
	return (last_cmd_status);
}
