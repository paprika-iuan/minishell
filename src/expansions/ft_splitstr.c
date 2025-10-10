/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:56:16 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:20:12 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

static int	is_split_ifs(char ch, char *c)
{
	while (*c)
	{
		if (ch == *c)
			return (1);
		c++;
	}
	return (0);
}

static int	count_words(const char *s, char *c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (is_split_ifs(*s, c))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**allocate_word(char **result, const char *s, int start, int len)
{
	int	j;

	j = 0;
	while (result[j])
		j++;
	result[j] = ft_substr(s, start, len);
	if (!result[j])
	{
		free_result(result, j);
		return (NULL);
	}
	return (result);
}

static char	**fill_result(char **result, const char *s, char *c)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	while (s[i])
	{
		while (s[i] && is_split_ifs(s[i], c))
			i++;
		start = i;
		while (s[i] && !is_split_ifs(s[i], c))
			i++;
		if (i > start)
		{
			result[j] = strndup(s + start, i - start);
			if (!result[j])
				return (free_result(result, j));
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_splitstr(char const *s, char *c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (words == 0)
		return (NULL);
	result = ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
		return (NULL);
	return (result);
}
