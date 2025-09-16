/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:54:04 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/16 14:54:06 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_operand(char c)
{
	return (c == AND || c == PIPE || c == P_OPEN ||
		c == P_CLOSE || c == RED_IN || c == RED_OUT);
}

void	count_word(char **line, int *count)
{
	while (**line && !is_whitespace(**line)
		&& !is_operand(**line) && !is_quote(**line))
		(*line)++;
	(*count)++;
}

void	count_quote(char **line, int *count)
{
	char	quote_type;
	char	*line_start;

	quote_type = **line;
	line_start = *line;
	(*line)++;
	while (**line && **line != quote_type)
		(*line)++;
	if (**line == quote_type)
	{
		(*count)++;
		(*line)++;
	}
	else
	{
		*line = line_start;
		(*count)++;
		(*line)++;
	}
}

void	count_operand(char **line, int *count)
{
	if (**line == PIPE || **line == RED_IN || **line == RED_OUT)
	{
		if (*(*line + 1) == **line)
			*line += 2;
		else
			*line += 1;
		(*count)++;
	}
	else if (**line == AND)
	{
		if (*(*line + 1) == AND)
		{
			*line += 2;
			(*count)++;
		}
		else
			(*line)++;
	}
	else if (**line == P_OPEN || **line == P_CLOSE)
	{
		(*line)++;
		(*count)++;
	}
}

int	count_tokens(char *line)
{
	int		count;

	count = 0;
	while (is_whitespace(*line))
		line++;
	while (*line)
	{
		if (is_quote(*line))
			count_quote(&line, &count);
		else if (is_operand(*line))
			count_operand(&line, &count);
		else if (!is_whitespace(*line))
			count_word(&line, &count);
		else
			line++;
	}
	return (count);
}
