/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:21:40 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/05 12:56:53 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_operand(char c)
{
	return (c == '&' || c == '|' || c == '('
		|| c == ')' || c == '<' || c == '>');
}

char	*allocate_token(int size)
{
	char	*token;

	token = malloc((size + 1) * sizeof(char));
	if (!token)
		return (NULL);
	return (token);
}

void	free_tokens(char **tokens, int i)
{
	while (--i >= 0)
		free(tokens[i]);
	free(tokens);
}

static int	scan_until_quote(char **line, char quote_type, char **backtrack_pos)
{
	int	len;
	int	found_whitespace;

	len = 0;
	found_whitespace = 0;
	while (**line && **line != quote_type)
	{
		if (is_whitespace(**line) && !found_whitespace)
		{
			*backtrack_pos = *line;
			found_whitespace = 1;
		}
		len++;
		(*line)++;
	}
	return (len);
}

int	handle_quote_length(char **line, int len)
{
	char	quote_type;
	char	*backtrack_position;

	quote_type = **line;
	backtrack_position = NULL;
	len++;
	(*line)++;
	len += scan_until_quote(line, quote_type, &backtrack_position);
	if (**line == quote_type)
	{
		len++;
		(*line)++;
	}
	else
		len = UNCLOSED_QUOTES;
	return (len);
}
