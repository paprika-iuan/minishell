/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:24:30 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/21 19:28:56 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	**fuse_dqvars(char *quotes, char *after, t_env *env)
{
	char	*expanded;
	char	**tmp_arr;

	expanded = ft_strdup(quotes);
	if (after && after[0])
	{
		tmp_arr = set_tmp_arr(after, env);
		tmp_arr = concat_before(tmp_arr, expanded);
		free(expanded);
		return (tmp_arr);
	}
	tmp_arr = malloc(sizeof(char *) * 2);
	if (!tmp_arr)
		return (NULL);
	tmp_arr[0] = ft_strdup(expanded);
	tmp_arr[1] = NULL;
	return (free(expanded), tmp_arr);
}

char	**set_tmp_arr(char *after, t_env *env)
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
		return (expanded_after);
	}
	return (res);
}

char	*do_expand_dollar_after(char *quotes, char *tmp, int i, t_env *env)
{
	char	*after;
	char	*after_expanded;
	char	*joined;

	after = ft_substr(quotes, i, ft_strlen(quotes));
	after_expanded = NULL;
	if (after && ft_strchr(after, '$'))
	{
		after_expanded = expand_dollar_line(after, env);
		joined = ft_strjoin(tmp, after_expanded);
		free(after_expanded);
	}
	else
	{
		joined = ft_strjoin(tmp, after);
		free(after);
	}
	return (joined);
}

char	*expand_dollar_line(char *quotes, t_env *env)
{
	int		i;
	char	*dollar;
	char	*before;
	char	*tmp;
	char	*res;

	i = 0;
	while (quotes[i] && quotes[i] != '$')
		i++;
	before = ft_substr(quotes, 0, i);
	dollar = dollar_expanded(quotes, env);
	i++;
	while (quotes[i] && (ft_isalnum(quotes[i]) || quotes[i] == '_'))
		i++;
	tmp = ft_strjoin(before, dollar);
	res = do_expand_dollar_after(quotes, tmp, i, env);
	return (free(quotes), free(before), free(dollar), free(tmp), res);
}

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
