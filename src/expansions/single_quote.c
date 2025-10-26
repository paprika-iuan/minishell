/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:52:33 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 12:11:23 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

void	update_case_n1(char **args, char *first, char *second)
{
	free(*args);
	*args = ft_strjoin(first, second);
}

void	update_tmp(char **args, int i, char *tmp, char *first_simple_quotes)
{
	if (tmp && tmp[0])
		update_case_n1(&args[i], first_simple_quotes, tmp);
	else
		update_case_n1(&args[i], first_simple_quotes, "");
}

char	**do_singlequote(char **args, int j, t_mini *mini)
{
	char	*first_simple_quotes;
	char	*expanded;
	char	**tmp;
	char	**tmp_arr;
	int		i;

	i = j;
	j = find_dollar(args[i], '\'', 0);
	first_simple_quotes = ft_substr(args[i], 0, j);
	if (args[i][j] && j != 0)
	{
		expanded = ft_substr(args[i], j, ft_strlen(args[i]));
		tmp_arr = malloc(sizeof(char *) * 2);
		if (!tmp_arr)
			return (free(first_simple_quotes), args);
		tmp_arr[0] = expanded;
		tmp_arr[1] = NULL;
		tmp = expand(tmp_arr, mini);
		update_tmp(args, i, tmp[0], first_simple_quotes);
		if (tmp && tmp != tmp_arr)
			free_matrix(tmp);
	}
	else
		update_case_n1(&args[i], first_simple_quotes, "");
	return (free(first_simple_quotes), args);
}
