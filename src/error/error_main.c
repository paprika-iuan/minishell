/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:35:50 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/24 12:38:25 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

int	no_input(char *input)
{
	if (!*input)
	{
		free(input);
		return (0);
	}
	return (1);
}

int	no_tokens(t_token *tokens, char *input, int *error, t_mini *mini)
{
	if (!tokens)
	{
		free(input);
		set_last_error(*error, mini);
		return (0);
	}
	return (1);
}

int	no_heredoc(int *error, t_NodeAST *ast_tree, t_mini *mini, char *input)
{
	*error = handle_heredocs(ast_tree, mini);
	signals_nonintmode();
	if (*error)
	{
		close_all_heredocs(ast_tree);
		free_ast(ast_tree);
		free(input);
		input = NULL;
		set_last_error(*error, mini);
		return (0);
	}
	return (1);
}

int	no_ast(int *error, t_NodeAST *ast_tree, char *input, t_mini *mini)
{
	if (*error)
	{
		free_ast(ast_tree);
		free(input);
		set_last_error(*error, mini);
		return (0);
	}
	return (1);
}
