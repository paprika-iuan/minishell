/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:05 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/14 16:43:07 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	pipe_node_redirections(t_NodeAST *node, t_mini *mini)
{
	if (!node)
		return (SUCCESS);
	if (node->type == NODE_SUBSHELL)
	{
		if (node->subshell.redirect
			&& !do_redirections(node->subshell.redirect, mini))
			return (FAILURE);
	}
	else if (node->type == NODE_CMD)
	{
		if (node->cmd.redirect
			&& !do_redirections(node->cmd.redirect, mini))
			return (FAILURE);
	}
	return (SUCCESS);
}

void	get_redir_flags(t_NodeAST *node, int *infile, int *outfile)
{
	t_NodeAST	*n_redir;

	n_redir = NULL;
	*infile = 0;
	*outfile = 0;
	if (!node)
		return ;
	if (node->type == NODE_SUBSHELL)
		n_redir = node->subshell.redirect;
	else
		n_redir = node->cmd.redirect;
	if (n_redir)
	{
		*outfile = has_outfile(n_redir);
		*infile = has_infile(n_redir);
	}
}

void	setup_pipe_cmd_fds(t_pipe_struct *t_pipe, t_NodeAST *node)
{
	int	infile;
	int	outfile;

	get_redir_flags(node, &infile, &outfile);
	if (t_pipe->pipe_idx == 0 && t_pipe->num_pipes > 0)
		dup2(t_pipe->pipes[1], STDOUT_FILENO);
	else if (t_pipe->pipe_idx == t_pipe->num_pipes)
		dup2(t_pipe->pipes[2 * (t_pipe->pipe_idx - 1)], STDIN_FILENO);
	else
	{
		dup2(t_pipe->pipes[2 * (t_pipe->pipe_idx - 1)], STDIN_FILENO);
		dup2(t_pipe->pipes[2 * t_pipe->pipe_idx + 1], STDOUT_FILENO);
	}
}
