/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:22:52 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/28 18:10:06 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

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

char	**case_no_ws(char *dollar)
{
	char	**split;

	split = ft_calloc(sizeof(char *), 2);
	if (!split)
		return (NULL);
	split[0] = ft_strdup(dollar);
	split[1] = NULL;
	return (split);
}
//after line 40
// if (!get_env_value("IFS", env))
// 	ifs = ' \t\n';
// else
// 	ifs = '';

//after line 56
// else if (ifs && ft_strcmp(ifs, "") == 0)
// 	split = do_ws_ifs(dollar, ifs);

//after line 64
// while (dollar[i])
// {
// 	if (is_ifs(dollar[i], env))
// 		dollar[i] = *ifs;
// 	i++;
// }

char	**do_word_splitting(char *dollar)
{
	int		i;
	char	*ifs;
	char	**split;
	char	**tmp;

	i = 0;
	split = NULL;
	tmp = NULL;
	ifs = " \t\n";
	if (ifs && ft_strcmp(ifs, " \t\n") == 0)
		split = ft_splitstr(dollar, ifs);
	if (!split || !split[0])
		tmp = case_no_ws(dollar);
	if (!split[0])
		free(split);
	free(dollar);
	if (tmp && tmp[0])
		return (tmp);
	return (split);
}

void	cleanup_vars(char *before, char *after, char **splited, char **a_s)
{
	if (before)
		free(before);
	if (after)
		free(after);
	if (a_s)
		free_matrix(a_s);
	if (splited)
		free_matrix(splited);
}

char	*set_context_before(char **args, int i)
{
	char	*before;

	if (args && args[i] && args[i][0] != '$')
	{
		before = set_before_dollar(args[i]);
		if (before && before[0])
			return (before);
		if (before)
			free (before);
	}
	return (NULL);
}
