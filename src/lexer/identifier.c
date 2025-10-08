/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:48:30 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/29 13:50:56 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

t_token	*tag_operand(char *op)
{
	t_token	*new_token;

	new_token = create_token(op);
	if (!new_token)
		return (NULL);
	if (op[0] == '<' && op[1])
		new_token->type = REDIR_HEREDOC;
	else if (op[0] == '>' && op[1])
		new_token->type = REDIR_OUT_APP;
	else if (op[0] == '<')
		new_token->type = REDIR_IN;
	else if (op[0] == '>')
		new_token->type = REDIR_OUT_TRUNC;
	else if (op[0] == '&')
		new_token->type = AND;
	else if (op[0] == '|' && op[1])
		new_token->type = OR;
	else if (op[0] == '|')
		new_token->type = PIPE;
	else
		new_token->type = SUBSHELL;
	return (new_token);
}

t_token	*tag_word(char *op)
{
	t_token	*new_token;

	new_token = create_token(op);
	if (!new_token)
		return (NULL);
	new_token->type = WORD;
	return (new_token);
}

t_token	*tag_and_validate(char *token_str, t_token *head, char **tok, int num)
{
	if (is_operand(token_str[0]))
	{
		if (token_str[0] == '&' && ft_strlen(token_str) == 1)
		{
			printf(SYNTAX_ERROR);
			return (NULL);
		}
		return (tag_operand(token_str));
	}
	return (tag_word(token_str));
}

t_token	*identifier(char **tokens, int *num_tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*node;
	int		i;

	if (!tokens)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (i < *num_tokens)
	{
		node = tag_and_validate(tokens[i], head, tokens, *num_tokens);
		if (!node)
		{
			free_token_list(head);
			return (NULL);
		}
		append_token(&head, &current, node);
		i++;
	}
	return (head);
}

t_token	*tokenizer(char *line)
{
	char	**raw_tokens;
	t_token	*id_tokens;
	int		num_tokens;

	raw_tokens = lexer(line, &num_tokens);
	if (!raw_tokens)
		return (NULL);
	id_tokens = identifier(raw_tokens, &num_tokens);
	free_tokens(raw_tokens, num_tokens);
	if (!id_tokens)
		return (NULL);
	else
		return (id_tokens);
}
