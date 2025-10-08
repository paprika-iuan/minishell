/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:41:27 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/01 11:15:38 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

t_NodeAST	*parse_ast(t_token *tokens, int *error)
{
	t_NodeAST	*head;

	head = NULL;
	if (!tokens)
		return (NULL);
	if (head == NULL && *error == 0)
		head = set_ao_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_pipe_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_subshell_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_cmd_node(tokens, error);
	return (head);
}

//Maybe fora crear una funcio per si queden tokens sense utilitzar.

void	free_redirect(t_NodeAST *node)
{
	t_NodeAST	*tmp;

	while (node)
	{
		tmp = node->redirect.redirect;
		free(node->redirect.file);
		free(node);
		node = tmp;
	}
}

void	free_ast(t_NodeAST *node)
{
	if (!node)
		return ;
	if (node->type == NODE_AND || node->type == NODE_OR
		|| node->type == NODE_PIPE)
	{
		free_ast(node->binary.left);
		free_ast(node->binary.right);
		free(node);
	}
	else if (node->type == NODE_SUBSHELL)
	{
		if (node->subshell.redirect)
			free_redirect(node->subshell.redirect);
		free_ast(node->subshell.reparse);
		free(node);
	}
	else
	{
		if (node->cmd.redirect)
			free_redirect(node->cmd.redirect);
		free_matrix(node->cmd.args);
		free(node);
	}
}
