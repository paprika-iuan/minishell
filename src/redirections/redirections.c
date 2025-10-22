/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:50:26 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/22 12:16:22 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

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

int	expansion_redirect(t_NodeAST *node, t_env *env)
{
	char	**before_expand;
	char	**expanded;

	if (node->redirect.type == REDIR_HEREDOC)
		return (SUCCESS);
	before_expand = malloc(2 * sizeof(char *));
	if (!before_expand)
		return (FAILURE);
	before_expand[0] = ft_strdup(node->redirect.file);
	before_expand[1] = NULL;
	expanded = expand(before_expand, env);
	if (expanded[1])
	{
		ft_putstr_fd("wanghao: ", STDERR_FILENO);
		ft_putstr_fd(node->redirect.file, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		free_matrix(expanded);
		return (FAILURE);
	}
	free(node->redirect.file);
	node->redirect.file = ft_strdup(expanded[0]);
	free_matrix(expanded);
	if (!node->redirect.file)
		return (FAILURE);
	return (SUCCESS);
}

int	do_redirections(t_NodeAST *node, t_env *env)
{
	int			fd;
	t_NodeAST	*curr;

	if (!node)
		return (SUCCESS);
	if (!expansion_redirect(node, env))
		return (FAILURE);
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
