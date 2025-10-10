/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:52:33 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:20:25 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

void	update_case_n1(char **args, char *first, char *second, int i)
{
	free(args[i]);
	args[i] = ft_strjoin(first, second);
}

void	do_singlequote(char **args, int i, t_env *env)
{
	char	*fist_simple_quotes;
	char	*expanded;
	char	*tmp;
	int		j;

	j = 0;
	j = find_dollar(args[i], '\'');
	first_simple_quotes = ft_substr(args[i], 0, j);
	expanded = ft_substr(args[i], j + 1, ft_strlen(args[i]));
	tmp = expand(&expanded, env);
	update_case_n1(args, first_simple_quotes, tmp, i);
	free(first_simple_quotes);
	free(tmp);
}
