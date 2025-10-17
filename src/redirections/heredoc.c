/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:51:13 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/14 12:51:15 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	get_heredoc(char *tmp_filename, t_NodeAST *node, int *status, t_env *n)
{
	char	*delimitter;
	int		write_fd;
	int		read_fd;

	delimitter = node->redirect.file;
	write_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (write_fd < 0)
	{
		*status = ERROR;
		return (print_file_error(tmp_filename), free(tmp_filename));
	}
	read_heredoc_input(write_fd, delimitter, n);
	close(write_fd);
	read_fd = open(tmp_filename, O_RDONLY);
	if (read_fd < 0)
	{
		*status = ERROR;
		return (print_file_error(tmp_filename), free(tmp_filename));
	}
	unlink(tmp_filename);
	free(delimitter);
	node->redirect.file = NULL;
	node->redirect.fd = read_fd;
	free(tmp_filename);
}

static void	process_here(t_NodeAST *redir, int *count, int *status, t_env *n)
{
	char	*tmp_filename;

	while (redir)
	{
		if (redir->redirect.type == REDIR_HEREDOC)
		{
			tmp_filename = make_here_name((*count)++);
			if (!tmp_filename)
			{
				*status = ERROR;
				return ;
			}
			get_heredoc(tmp_filename, redir, status, n);
		}
		redir = redir->redirect.redirect;
	}
}

void	heredoc_iter(t_NodeAST *n, int *counter, int *status, t_env *env)
{
	if (!n)
		return ;
	if (n->type == NODE_CMD)
	{
		process_here(n->cmd.redirect, counter, status, env);
		return ;
	}
	if (n->type == NODE_SUBSHELL)
	{
		heredoc_iter(n->subshell.reparse, counter, status, env);
		process_here(n->subshell.redirect, counter, status, env);
		return ;
	}
	if (n->type == NODE_PIPE || n->type == NODE_AND || n->type == NODE_OR)
	{
		heredoc_iter(n->binary.left, counter, status, env);
		heredoc_iter(n->binary.right, counter, status, env);
		return ;
	}
}

int	handle_heredocs(t_NodeAST *node, t_env *env)
{
	int		counter;
	int		status;

	counter = 0;
	status = 0;
	heredoc_iter(node, &counter, &status, env);
	return (status);
}
