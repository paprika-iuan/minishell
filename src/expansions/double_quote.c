/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:13:51 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/16 18:38:39 by jgirbau-         ###   ########.fr       */
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
	char	**copy;
	int		count;
	int		j;

	j = 0;
	count = 0;
	after_splited = NULL;
	copy = NULL;
	while (res[0][j] && count != 2)
	{
		if (res[0][j] == '"')
			count++;
		j++;
	}
	before = ft_substr(res[0], 0, j);
	after = ft_substr(res[0], j, ft_strlen(res[0]) - j);
	if (after && after[0])
	{
		after_splited = expand_if_dollar(after, env);
		free(after);
		free(args[i]);
		args[i] = ft_strjoin(before, after_splited[0]);
		free(before);
		args = join_matrix(args, &after_splited[1]);
		free_matrix(after_splited);
	}
	/*else
	{
		free(args[i]);
		args[i] = ft_strdup(before);
		free(before);
		free(after);
		return (args);
	}*/
	return (args);
}
/*
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
	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = set_expansion_return(dollar, before, after);
	res[1] = NULL;
	len = 0;
	if (before)
		len += ft_strlen(before);
	if (dollar)
		len += ft_strlen(dollar);
	if (res[0] && ft_strchr(res[0] + len, '$'))
		args = expand_after_dq(args, res, env, i);
	else
		args = update_matrix(args, res, i);
	free_matrix(res);
	return (args);
}*/

char	*extract_str(char **args, int i, int begin_join, int num_appear)
{
	int		j;
	int		count;
	char	*res;

	j = begin_join;
	count = 0;
	while (args[i] && args[i][j] && count != num_appear)
	{
		if (args && (args[i][j] == '"'))
			count++;
		j++;
	}
	if (j == (int)ft_strlen(args[i]) || count == num_appear)
	{
		res = ft_substr(args[i], begin_join, j - begin_join);
		return (res);
	}
	return (NULL);
}

char *expand_dollar_line(char *quotes, t_env *env)
{
	int		i;
	char	*dollar;
	char	*before;
	char	*tmp;
	char	*res;
	char	*after;
	char	*after_expanded;

	i = 0;
	while (quotes[i] && quotes[i] != '$')
		i++;
	before = ft_substr(quotes, 0, i);
	dollar = dollar_expanded(quotes, env);
	i++;
	while (quotes[i] && (ft_isalnum(quotes[i]) || quotes[i] == '_'))
		i++;
	tmp = ft_strjoin(before, dollar);
	after = ft_substr(quotes, i, ft_strlen(quotes));
	after_expanded = NULL;
	if (after && ft_strchr(after, '$'))
	{
		after_expanded = expand_dollar_line(after, env);
		res = ft_strjoin(tmp, after_expanded);
	}
	else
		res = ft_strjoin(tmp, after);
	free(before);
	free(dollar);
	free(after);
	free(tmp);
	return (res);
}

char **set_tmp_arr(char *after, t_env *env)
{
	char	**res;
	char	**expanded_after;

	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(after);
	res[1] = NULL;
	if (after && ft_strchr(after, '$'))
	{
		expanded_after = expand(res, env);
		//free_matrix(res);
		return (expanded_after);
	}
	return (res);
}

char	**fuse_dqvars(char *quotes, char *after, t_env *env)
{
	char	*expanded;
	char	**tmp_arr;

	expanded = ft_strdup(quotes);
	if (after && after[0])
	{
		tmp_arr = set_tmp_arr(after, env);
		tmp_arr = concat_before(tmp_arr, expanded);
		return (tmp_arr);
	}
	tmp_arr = malloc(sizeof(char *) * 2);
	if (!tmp_arr)
		return (NULL);
	tmp_arr[0] = ft_strdup(expanded);
	tmp_arr[1] = NULL;
	free(expanded);
	return (tmp_arr);
}

char	**do_doublequote(char **args, int i, t_env *env)
{
	char	*quotes;
	char	*after;
	char	**tmp_arr;
	char	**res;

	//before = extract_str(args, i, 0, 1	);
	//dprintf(2, "before-----------%s\n", before);
	quotes = extract_str(args, i, 0, 2);
	//dprintf(2, "quotes-----------%s\n", quotes);
	//dprintf(2, "quotes-----------%s\n", quotes);
	after = extract_str(args, i, (ft_strlen(quotes)), 3);
	//dprintf(2, "after-----------%s\n", after);
	quotes = expand_dollar_line(quotes, env);
	tmp_arr = NULL;
	if (after || quotes)
		tmp_arr = fuse_dqvars(quotes, after, env);
	res = update_matrix(args, tmp_arr, i);
	free(quotes);
	free(after);
	free_matrix(tmp_arr);
	return (res);
}
