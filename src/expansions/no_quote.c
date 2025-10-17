/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:33:32 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/17 11:06:30 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	**case_no_ws(char *dollar)
{
	char **split;
	
	split = malloc(sizeof(char *) * 2);
	if (!split)
		return NULL;
	if (split[0])
		split[0] = ft_strdup(dollar);
	else
	{
		split[0] = NULL;
		split[1] = NULL;
	}	
	return (split);
}

char	**do_word_splitting(char *dollar, t_env *env)
{
	int		i;
	char	*ifs;
	char	**split;

	i = 0;
	split = NULL;
	if (!get_env_value("IFS", env))
		ifs = " \t\n";
	else
		ifs = "";
	while (dollar[i])
	{
		if (is_ifs(dollar[i], env))
			dollar[i] = *ifs;
		i++;
	}
	if (ifs && strcmp(ifs, " \t\n") == 0)
		split = ft_splitstr(dollar, ifs);
	else if (ifs && strcmp(ifs, "") == 0)
		split = do_ws_ifs(dollar, ifs);
	if (!split)
		split = case_no_ws(dollar);
	else
		free(dollar);
	return (split);
}

void	cleanup_vars(char *before, char *after, char **splited, char **after_splited)
{
	if (before)
		free(before);
	if (after)
		free(after);
	if (after_splited)
		free_matrix(after_splited);
	if (splited && splited[0] && splited[0][0])
		free_matrix(splited);
}

char	*set_context_before(char **args, int i)
{
	char *before;

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

char	**expand_if_dollar(char *args, t_env *env)
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
		tmp = expand(res_arr, env);
		//free_matrix(res_arr);
		return (tmp);
	}
	return (res_arr);
}

char	**do_noquote(char **args, int i, t_env *env)
{
	char	*dollar;
	char	*before;
	char	*after;
	char	**after_splited;
	char	**splited;

	dollar = dollar_expanded(args[i], env);
	//dprintf(2, "dollar---%s\n", dollar);
	after_splited = NULL;
	splited = NULL;
	before = set_context_before(args, i);
	//dprintf(2, "dbefore---%s\n", before);
	after = set_context_after(args, i);
	//dprintf(2, "after---%s\n", after);
	if (dollar)
	{
		splited = do_word_splitting(dollar, env);
		//printf("Si\n");
		if (splited && (before || after))
		{
			splited = concat_before(splited, before);
			//dprintf(2, "splited---%s\n", splited[0]);
			if (after && after[0])
			{
				after_splited = expand_if_dollar(after, env);
				//printf("Su\n");
				splited = concat_after(splited, after_splited);
			}
		}
		args = update_matrix(args, splited, i);
	}
	else if (after)
	{
		
		after_splited = expand_if_dollar(after, env);
		args = update_no_ws_expansion(args, i, before, after_splited);
	}
	else
	{
		dollar = malloc(1);
		dollar = "''";
		free(args[i]);
		args[i] = ft_strdup(dollar);
		//return (args);
	}
	cleanup_vars(before, after, splited, after_splited);
	return (args);
}
