/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:49:35 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/21 17:17:54 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	**update_matrix(char **args, char **splited, int i)
{
	int		a;
	int		s;
	int		j;
	int		k;
	char	**res;

	j = 0;
	a = ft_arraylen(args);
	s = ft_arraylen(splited);
	res = malloc(sizeof(char *) * (a + s + 1));
	if (!res)
		return (NULL);
	k = 0;
	while (k < i)
	{
		res[k] = ft_strdup(args[k]);
		k++;
	}
	while (j < s)
		res[k++] = ft_strdup(splited[j++]);
	s = i + 1;
	while (s < a)
		res[k++] = ft_strdup(args[s++]);
	res[k] = NULL;
	return (free_matrix(args), res);
}

char	**concat_before(char **splited, char *before)
{
	char	*tmp;

	if (before)
	{
		tmp = ft_strjoin(before, splited[0]);
		free(splited[0]);
		splited[0] = ft_strdup(tmp);
		free(tmp);
	}
	return (splited);
}

void	loop_after_len(char **res, int *i, int after_len, char **after)
{
	int		j;

	j = 0;
	while (j + 1 < after_len)
	{
		res[*i] = ft_strdup(after[j + 1]);
		(*i)++;
		j++;
	}
}

char	**update_matrix_after(char **splited, char **after)
{
	int		splited_len;
	int		after_len;
	char	**res;
	int		i;

	i = 0;
	after_len = ft_arraylen(after);
	splited_len = ft_arraylen(splited);
	res = NULL;
	if ((after_len + splited_len) > 1)
	{
		res = malloc(sizeof(char *) * ((splited_len - 1 + after_len) + 1));
		if (!res)
			return (NULL);
		while (i < splited_len)
		{
			res[i] = ft_strdup(splited[i]);
			i++;
		}
		loop_after_len(res, &i, after_len, after);
		res[i] = NULL;
	}
	return (res);
}

char	**concat_after(char **splited, char **after)
{
	int		j;
	char	*tmp;
	char	**res;

	if (!after || !after[0])
		return (splited);
	res = NULL;
	j = ft_arraylen(splited) - 1;
	tmp = ft_strjoin(splited[j], after[0]);
	free(splited[j]);
	splited[j] = ft_strdup(tmp);
	free(tmp);
	if (after[1] && after[1][0])
	{
		res = update_matrix_after(splited, after);
		free_matrix(splited);
		return (res);
	}
	return (splited);
}

char	**update_no_ws_exp(char **args, int i, char *before, char **after)
{
	if (before)
		update_case_n2(&args[i], before);
	else if (after)
	{
		args = update_matrix(args, after, i);
		after = NULL;
	}
	else if (!before && !after)
		args[i] = NULL;
	return (args);
}
