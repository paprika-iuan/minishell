/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:15:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 14:09:54 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"
#include "../../inc/expansion.h"

int	find_end_var(char *args)
{
	int	i;

	i = 0;
	while (args[i] && args[i] != '$')
		i++;
	if (!args[i])
		return (i);
	i++;
	while (args[i] && (ft_isalnum(args[i]) || args[i] == '_'
			|| args[i] == '?'))
		i++;
	return (i);
}

void	hide_quotes(char *args, int j, int i)
{
	int	k;

	k = i + 1;
	while (k < j)
	{
		if (args[k] == '\'')
			args[k] = 5;
		else if (args[k] == '"')
			args[k] = 6;
		k++;
	}
}

char	*respect_quotes(char *args)
{
	int		i;
	int		j;
	char	q_type;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			q_type = args[i];
			j = find_closure(args, q_type, i);
			if (j)
			{
				hide_quotes(args, j, i);
				i = j + 1;
				continue ;
			}
		}
		i++;
	}
	return (args);
}

char	**expand(char **args, t_env *env)
{
	int	n;
	int	i;

	i = 0;
	while (args && args[i])
	{
		n = expansion_type(args[i]);
		if (n == 3)
			args[i] = respect_quotes(args[i]);
		else if (n == 2)
			args = do_doublequote(args, i, env);
		else if (n == 1)
			args = do_singlequote(args, i, env);
		else if (n == 0)
			args = do_noquote(args, i, env);
		i++;
	}
	return (args);
}
