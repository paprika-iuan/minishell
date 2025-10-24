/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:15:55 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 13:15:57 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	print_file_error(char *filename)
{
	ft_putstr_fd("wanghao: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd(": error opening file\n", STDERR_FILENO);
}

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
		print_file_error(node->redirect.file);
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
