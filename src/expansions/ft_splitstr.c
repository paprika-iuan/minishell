/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:56:16 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/28 15:12:28 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	**free_result(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
	return (NULL);
}

int	is_split_ifs(char ch, char *c)
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

static char	**fill_result(char **result, const char *s, char *c)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_split_ifs(s[i], c))
			i++;
		start = i;
		while (s[i] && !is_split_ifs(s[i], c))
			i++;
		if (i > start)
		{
			result[j] = ft_strndup(s + start, i - start);
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
	result = ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
		return (NULL);
	return (result);
}
