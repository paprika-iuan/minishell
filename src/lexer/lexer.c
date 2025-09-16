/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:06:29 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/15 13:06:31 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*allocate_token(int size)
{
	char	*token;

	token = malloc(size * sizeof(char));
	if (!token)
		return (NULL);
	return (token);
}

void	fill_word(char **line)
{

}

char	*fill_operand(char **line)
{
	char	*token;

	token = NULL;
	if (**line == PIPE || **line == RED_IN || **line == RED_OUT)
	{
		if (*(*line + 1) == **line)
		{
			token = allocate_token(3);
		}
	}
	else if (**line == AND)
	{}
	else if (**line == P_OPEN || **line == P_CLOSE)
	{}
	return (token);
}

void	fill_quote()
{

}

int	fill_tokens(char **tokens, char *line)
{

	while (*line)
	{
		while (is_whitespace(*line))
			line++;
		if (is_quote(*line))
			fill_quote(&line);
		else if (is_operand(*line))
			fill_operand(&line);
		else
			fill_word(&line);
	}
	return (SUCCESS);
}

char	**tokenizer(char *line)
{
	char	**tokens;
	int		num_tokens;

	if (!line)
		return (NULL);
	num_tokens = count_tokens(line);
	tokens = malloc((num_tokens + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!fill_tokens(tokens, line))
		return (NULL);
	return (tokens);
}
