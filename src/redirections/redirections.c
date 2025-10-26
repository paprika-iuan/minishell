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

int	expansion_redirect(t_NodeAST *node, t_mini *mini)
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
	expanded = expand(before_expand, mini);
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

int	do_redirections(t_NodeAST *node, t_mini *mini)
{
	int			fd;
	t_NodeAST	*curr;

	if (!node)
		return (SUCCESS);
	if (!expansion_redirect(node, mini))
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
