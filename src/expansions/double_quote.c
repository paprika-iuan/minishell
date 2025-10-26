/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:13:51 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 13:28:46 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

void	update_case_n2(char **args, char *expanded)
{
	free(*args);
	*args = ft_strdup(expanded);
}

char	**do_doublequote(char **args, int i, t_mini *mini)
{
	char	*quotes;
	char	*after;
	char	**tmp_arr;
	char	**res;

	quotes = extract_str(args, i, 0, 2);
	after = extract_str(args, i, (ft_strlen(quotes)), 3);
	quotes = expand_dollar_line(quotes, mini);
	tmp_arr = NULL;
	if (after || quotes)
		tmp_arr = fuse_dqvars(quotes, after, mini);
	res = update_matrix(args, tmp_arr, i);
	free(quotes);
	free(after);
	free_matrix(tmp_arr);
	return (res);
}
