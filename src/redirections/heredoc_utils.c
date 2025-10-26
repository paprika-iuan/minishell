/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:11:27 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/20 10:26:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*make_here_name(int id)
{
	char	*num;
	char	*name;
	char	*tmp;

	num = ft_itoa(id);
	tmp = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	name = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (name);
}

static void	close_heredocs_in_redirects(t_NodeAST *redir)
{
	while (redir)
	{
		if (redir->redirect.type == REDIR_HEREDOC
			&& redir->redirect.fd >= 0)
			close(redir->redirect.fd);
		redir = redir->redirect.redirect;
	}
}

void	close_all_heredocs(t_NodeAST *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		close_heredocs_in_redirects(node->cmd.redirect);
		return ;
	}
	if (node->type == NODE_SUBSHELL)
	{
		close_all_heredocs(node->subshell.reparse);
		close_heredocs_in_redirects(node->subshell.redirect);
		return ;
	}
	if (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR)
	{
		close_all_heredocs(node->binary.left);
		close_all_heredocs(node->binary.right);
		return ;
	}
}
