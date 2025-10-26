/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herequotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:15:21 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/26 13:15:23 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	has_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

char	*append_substr(char *result, char *src, int len)
{
	char	*tmp;
	char	*new_result;

	if (len == 0)
		return (result);
	tmp = ft_strndup(src, len);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	new_result = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (new_result);
}

static char	*process_quoted_section(char *result, char **curr)
{
	char	quote_char;
	int		i;

	quote_char = **curr;
	(*curr)++;
	i = 0;
	while ((*curr)[i] && (*curr)[i] != quote_char)
		i++;
	if (i > 0)
		result = append_substr(result, *curr, i);
	if ((*curr)[i] == quote_char)
		*curr += i + 1;
	else
		*curr += i;
	return (result);
}

char	*remove_quotes(char *str)
{
	char	*result;
	char	*curr;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	curr = str;
	while (*curr)
	{
		i = 0;
		while (curr[i] && !is_quote(curr[i]))
			i++;
		if (i > 0)
		{
			result = append_substr(result, curr, i);
			curr += i;
		}
		if (*curr && is_quote(*curr))
			result = process_quoted_section(result, &curr);
	}
	return (result);
}
