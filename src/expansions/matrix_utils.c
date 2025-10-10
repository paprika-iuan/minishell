/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:49:35 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:20:21 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

char	**update_matrix(char **args, char **splited, int i)
{
	int		a;
	int		s;
	int		j;
	int		k;
	char	**res;

	j = 0;
	a = ft_arraylen(args);
	s = ft_arraylen(splited);
	res = malloc(sizeof(char *) * (a + s + 1));
	if (!res)
		return (NULL);
	k = 0;
	while (j < i)
		res[j++] = args[k++];
	a = 0;
	while (a < s)
		res[j++] = splited[a++];
	k = i + 1;
	while (args[k])
		res[j++] = args[k++];
	res[j] = NULL;
	free_matrix(args);
	free_matrix(splited);
	return (res);
}

void	concat_before(char **args, char *splited, char *before, int i)
{
	char	*tmp;

	if (before)
	{
		tmp = ft_strjoin(before, splited[0]);
		free(splited[0]);
		splited[0] = ft_strdup(tmp);
		free(tmp);
		args = update_matrix(args, splited, i);
	}
	return ;
}

void	concat_after(char **args, char *splited, char *after, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	j = ft_arraylen(splited);
	if (after)
	{
		tmp = ft_strjoin(splited[j], after);
		free(splited[j]);
		splited[j] = ft_strdup(tmp);
		free(tmp);
		args = update_matrix(args, splited, i);
		return ;
	}
	return ;
}

void	update_no_ws_expansion(char **args, int i, char *before, char *after)
{
	if (before && after)
		update_case_n1(before, after, i);
	else if (before && !after)
		update_case_n2(args, before, i);
	else if (!before && after)
		update_case_n2(args, after, i);
}
