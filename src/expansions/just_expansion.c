/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:33:32 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:20:18 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

char	**do_word_splitting(char *dollar, t_env *env)
{
	int		i;
	char	*ifs;
	char	**split;

	i = 0;
	if (!get_env_value("IFS", env))
		ifs = ' \t\n';
	else
		ifs = '';
	while (dollar)
	{
		if (is_ifs(dollar[i], env))
			dollar[i] = ifs;
	}
	if (ifs && ifs == ' \t\n')
		spilt = ft_splitstr(dollar, ifs);
	else if (ifs && ifs == '')
		split = do_ws_ifs(dollar, ifs);
	free(dollar);
	return (split);
}

void	cleanup_vars(char *before, char *after, char *splited)
{
	if (before)
		free(before);
	if (after)
		free(after);
	if (splited)
		free(splited);
}

char	**do_just_expansion(char **args, int i, t_env *env)
{
	char	*dollar;
	char	*before;
	char	*after;
	char	**splited;

	dollar = dollar_expanded(args[i], env);
	before = set_before_dollar(args[i]);
	after = set_after_dollar(args[i]);
	if (dollar)
	{
		splited = do_word_splitting(dollar, env);
		free(dollar);
		if (splited && (before || after))
		{
			concat_before(args, splited, before, i);
			concat_after(args, splited, after, i);
		}
		else if (splited && !before && !after)
			args = update_matrix(args, splited, i);
	}
	else
		update_no_ws_expansion(args, i, before, after);
	args = expand(args, env);
	cleanup_vars(before, after, splited);
	return (args);
}
