/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:13:51 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/15 17:39:56 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char **join_matrix(char **a, char **b)
{
	int len_a = ft_arraylen(a);
	int len_b = ft_arraylen(b);
	char **res;
	int i = 0, j = 0;

	res = malloc(sizeof(char *) * (len_a + len_b + 1));
	if (!res)
		return NULL;
	while (i < len_a)
	{
		res[i] = ft_strdup(a[i]);
		i++;
	}
	while (j < len_b)
	{
		res[i++] = ft_strdup(b[j++]);
	}
	res[i] = NULL;
	return res;
}

void	update_case_n2(char **args, char *expanded)
{
	free(*args);
	*args = ft_strdup(expanded);
}

char	*set_expansion_return(char *dollar, char *before, char *after)
{
	char	*bottom;
	char	*res;

	if (dollar && after && before)
	{
		bottom = ft_strjoin(dollar, after);
		free(dollar);
		free(after);
		res = ft_strjoin(before, bottom);
		free(before);
		free(bottom);
		return (res);
	}
	if (dollar && after && !before)
	{
		res = ft_strjoin(dollar, after);
		free(dollar);
		free(after);
		return (res);
	}
	if (dollar && !after && !before)
		return (dollar);
	return (NULL);
}

char	**expand_after_dq(char **args, char **res, t_env *env, int i)
{
	char	**after_splited;
	char	*before;
	char	*after;
	int		count;
	int		j;

	j = 0;
	count = 0;
	while (res[0][j] && count != 2)
	{
		if (res[0][j] == '"')
			count++;
		j++;
	}
	before = ft_substr(res[0], 0, j);
	after = ft_substr(res[0], j, ft_strlen(res[0]) - j);
	after_splited = expand_if_dollar(after, env);
	free(after);
	free(args[i]);
	args[i] = ft_strjoin(before, after_splited[0]);
	free(before);
	args = join_matrix(args, &after_splited[1]);
	free_matrix(after_splited);
	return (args);
}

char	**do_doublequote(char **args, int i, t_env *env)
{
	char	*dollar;
	char	*before;
	char	*after;
	char	**res;
	int		len;

	dollar = dollar_expanded(args[i], env);
	before = set_before_dollar(args[i]);
	after = set_after_dollar(args[i]);
	len = 0;
	if (before)
		len += ft_strlen(before);
	if (dollar)
		len += ft_strlen(dollar);
	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = set_expansion_return(dollar, before, after);
	res[1] = NULL;
	if (res[0] && ft_strchr(res[0] + len, '$'))
		args = expand_after_dq(args, res, env, i);
	else
		args = update_matrix(args, res, i);
	free_matrix(res);
	return (args);
}

