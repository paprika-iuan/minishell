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

int is_operand(char c)
{
    return (c == AND || c == PIPE || c == P_OPEN ||
            c == P_CLOSE || c == RED_IN || c == RED_OUT);
}

int	count_tokens(char *line)
{
	int		count;
	char	quote_type;

	count = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			quote_type = *line;
			line++;
			while (*line && *line != quote_type)
				line++;
			if (*line)
				count++;
		}
		else if (is_operand(*line))
		line++;
	}
	return (count);
}

char	**tokenizer(char *line)
{
	char **tokens;
	int	num_tokens;

	tokens = malloc(num_tokens * sizeof(char *));
	if (!line)
		return (NULL);
	while (*line)
	{

		line++;
	}

	return (tokens);
}
