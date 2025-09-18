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

int	get_operand_length(char *line)
{
	if (*line == '|' || *line == '<' || *line == '>' || *line == '&')
	{
		if (*(line + 1) == *line)
			return (2);
		else
			return (1);
	}
	else if (*line == '(' || *line == ')')
		return (1);
	return (0);
}

int	get_word_length(char *line)
{
	int		len;

	len = 0;
	while (*line && !is_whitespace(*line) && !is_operand(*line))
	{
		if (is_quote(*line))
			len = handle_quote_length(&line, len);
		else
		{
			len++;
			line++;
		}
	}
	return (len);
}

void	count_word(char **line, int *count)
{
	int	len;

	len = get_word_length(*line);
	(*line) += len;
	(*count)++;
}

void	count_operand(char **line, int *count)
{
	int	len;

	len = get_operand_length(*line);
	if (len > 0)
	{
		(*line) += len;
		(*count)++;
	}
	else if (**line == '&')
		(*line)++;
}

int	count_tokens(char *line)
{
	int		count;

	count = 0;
	while (is_whitespace(*line))
		line++;
	while (*line)
	{
		if (is_operand(*line))
			count_operand(&line, &count);
		else if (!is_whitespace(*line))
			count_word(&line, &count);
		else
			line++;
	}
	return (count);
}
