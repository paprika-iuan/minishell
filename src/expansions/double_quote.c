/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:13:51 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:19:41 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

void	update_case_n2(char **args, char *expanded, int i)
{
	free(args[i]);
	args[i] = ft_strdup(expanded);
	free(expanded);
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
}

char	*do_expansion(char *args, t_env *env)
{
	char	*dollar;
	char	*before;
	char	*after;
	char	*res;

	dollar = dolar_expanded(args, env);
	before = set_before_dollar(args);
	after = set_after_dollar(args);
	res = set_expansion_return(dollar, before, after);
	return (res);
}

void	do_doublequote(char **args, int i, t_env *env)
{
	char	*expanded;

	expanded = do_expansion(args[i], env);
	update_case_n2(args, expanded, i);
	if (ft_strchr(args[i], '$'))
		args = expand(args[i], env);
	else
		return ;
}
