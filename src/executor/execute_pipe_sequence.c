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
	t_NodeAST	*curr;

	curr = node;
	if (pipe_idx == 0)
		return (curr->binary.left);
	while (pipe_idx > 1 && curr->binary.right
		&& curr->binary.right->type == NODE_PIPE)
	{
		curr = curr->binary.right;
		pipe_idx--;
	}
	if (curr->binary.right)
	{
		if (curr->binary.right->type == NODE_PIPE)
			return (curr->binary.right->binary.left);
		else
			return (curr->binary.right);
	}
	return (NULL);
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
		current_cmd = get_current_cmd(node, t_pipe->pipe_idx);
		if (!pipe_node_redirections(current_cmd))
			exit(ERROR);
		setup_pipe_cmd_fds(t_pipe, current_cmd);
		close_pipes(t_pipe);
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
