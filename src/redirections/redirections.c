/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:50:26 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/26 17:50:28 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	open_file(t_NodeAST *node)
{
	int			fd;

	if (node->redirect.type == REDIR_IN)
		fd = open(node->redirect.file, O_RDONLY);
	else if (node->redirect.type == REDIR_OUT_TRUNC)
		fd = open(node->redirect.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->redirect.type == REDIR_OUT_APP)
		fd = open(node->redirect.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = node->redirect.fd;
	if (fd < 0)
	{
		if (errno == ENOENT)
		{
			// stderr
			printf("wanghao: %s: ", node->redirect.file);
			printf("No such file or directory\n");
		}
		else if (errno == EACCES)
			printf("wanghao: %s: Permission denied\n", node->redirect.file);
	}
	return (fd);
}

int	has_infile(t_NodeAST *node)
{
	t_NodeAST	*curr;

	if (!node)
		return (FAILURE);
	curr = node;
	while (curr)
	{
		if (curr->redirect.type == REDIR_IN
			|| curr->redirect.type == REDIR_HEREDOC)
			return (SUCCESS);
		curr = curr->redirect.redirect;
	}
	return (FAILURE);
}

int	has_outfile(t_NodeAST *node)
{
	t_NodeAST	*curr;

	if (!node)
		return (FAILURE);
	curr = node;
	while (curr)
	{
		if (curr->redirect.type == REDIR_OUT_APP
			|| curr->redirect.type == REDIR_OUT_TRUNC)
			return (SUCCESS);
		curr = curr->redirect.redirect;
	}
	return (FAILURE);
}

int	do_redirections(t_NodeAST *node)
{
	int			fd;
	t_NodeAST	*curr;

	if (!node)
		return (SUCCESS);
	curr = node;
	while (curr)
	{
		fd = open_file(curr);
		if (fd < 0)
			return (FAILURE);
		if (curr->redirect.type == REDIR_IN
			|| curr->redirect.type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		curr = curr->redirect.redirect;
	}
	return (SUCCESS);
}
