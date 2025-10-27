/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:33:32 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 11:09:49 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	*set_context_after(char **args, int i)
{
	char	*after;

	if (args && args[i])
	{
		after = set_after_dollar(args[i]);
		if (after && after[0])
			return (after);
		if (after)
			free (after);
	}
	return (NULL);
}

char	**expand_if_dollar(char *args, t_mini *mini)
{
	char	**res_arr;
	char	**tmp;

	res_arr = malloc(sizeof(char *) * 2);
	if (!res_arr)
		return (NULL);
	res_arr[0] = ft_strdup(args);
	res_arr[1] = NULL;
	if (ft_strchr(res_arr[0], '$'))
	{
		tmp = expand(res_arr, mini);
		return (tmp);
	}
	return (res_arr);
}

char	**rebuild_str_nq(char **splited, char *before, char *after, t_mini *m)
{
	char	**after_splited;

	after_splited = NULL;
	if (splited && (before || after))
	{
		splited = concat_before(splited, before);
		if (after && after[0])
		{
			after_splited = expand_if_dollar(after, m);
			splited = concat_after(splited, after_splited);
			free_matrix(after_splited);
		}
	}
	return (splited);
}

void	case_no_dollar_nq(char *dollar, char **args, int i)
{
	dollar = ft_strdup("");
	free(args[i]);
	args[i] = ft_strdup(dollar);
	free(dollar);
}

char	**do_noquote(char **args, int i, t_mini *mini)
{
	char	*dollar;
	char	*before;
	char	*after;
	char	**after_splited;
	char	**splited;

	dollar = dollar_expanded(args[i], mini);
	after_splited = NULL;
	splited = NULL;
	before = set_context_before(args, i);
	after = set_context_after(args, i);
	if (dollar)
	{
		splited = do_word_splitting(dollar);
		splited = rebuild_str_nq(splited, before, after, mini);
		args = update_matrix(args, splited, i);
	}
	else if (after)
	{
		after_splited = expand_if_dollar(after, mini);
		args = update_no_ws_exp(args, i, before, after_splited);
	}
	else
		case_no_dollar_nq(dollar, args, i);
	return (cleanup_vars(before, after, splited, after_splited), args);
}
