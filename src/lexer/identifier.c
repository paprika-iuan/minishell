/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:48:30 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/18 15:49:41 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_token(char *content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

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

t_token	*identifier(char **tokens, int	*num_tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;

	if (!tokens)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (i < *num_tokens)
	{
		if (is_operand(tokens[i][0]))
		{
			if (tokens[i][0] == '&' && ft_strlen(tokens[i]) == 1)
				return (NULL); // syntax error
			new_token = tag_operand(tokens[i]);
		}
		else
			new_token = tag_word(tokens[i]);
		if (!new_token)
			return (NULL);
		new_token->position = i;
		if (head == NULL)
		{
			head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
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
	id_tokens = identifier(raw_tokens, &num_tokens);
	return (id_tokens);
}
