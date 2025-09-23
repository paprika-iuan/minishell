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

static char	*create_and_fill_token(char **line, int len)
{
	char	*token;
	int		i;

	if (len == 0)
		return (NULL);
	token = allocate_token(len);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = **line;
		(*line)++;
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*fill_word(char **line)
{
	int	len;

	len = get_word_length(*line);
	return (create_and_fill_token(line, len));
}

char	*fill_operand(char **line)
{
	int	len;

	len = get_operand_length(*line);
	return (create_and_fill_token(line, len));
}

int	fill_tokens(char **tokens, char *line)
{
	int		i;
	char	*new_token;

	i = 0;
	while (*line)
	{
		while (is_whitespace(*line))
			line++;
		if (!*line)
			break ;
		if (is_operand(*line))
			new_token = fill_operand(&line);
		else
			new_token = fill_word(&line);
		if (!new_token)
			return (free_tokens(tokens, i), FAILURE);
		tokens[i++] = new_token;
	}
	tokens[i] = NULL;
	return (SUCCESS);
}

char	**lexer(char *line, int	*num_tokens)
{
	char	**tokens;

	if (!line)
		return (NULL);
	*num_tokens = count_tokens(line);
	tokens = malloc((*num_tokens + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!fill_tokens(tokens, line))
		return (NULL);
	return (tokens);
}
