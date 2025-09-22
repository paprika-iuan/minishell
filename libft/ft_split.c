/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:00:35 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/16 15:01:04 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static void	free_result(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
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

static char	**fill_result(char **result, const char *s, char c)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			len = i - start;
			if (!allocate_word(result, s, start, len))
				return (NULL);
		}
		else
			i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
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
