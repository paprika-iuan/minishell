/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:39:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/28 15:25:27 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

int	count_quotes(char *args)
{
	int		i;
	int		count;
	char	qt;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			qt = args[i];
			i++;
		}
		else
		{
			advance_both(&count, &i);
			continue ;
		}
		while (args[i] && args[i] != qt)
			advance_both(&count, &i);
		i++;
	}
	return (count);
}

void	del_qt_loop(int *i, int *k, char *args, char *tmp)
{
	char	qt;
	int		qt_next_pos;

	while (args[*i])
	{
		if (args[*i] == '\'' || args[*i] == '"')
		{
			qt = args[*i];
			qt_next_pos = find_closure(args, qt, *i);
			if (qt_next_pos && qt_next_pos > *i)
			{
				(*i)++;
				while (*i < qt_next_pos)
					tmp[(*k)++] = args[(*i)++];
				(*i)++;
				continue ;
			}
			else
			{
				(*i)++;
				continue ;
			}
		}
		tmp[(*k)++] = args[(*i)++];
	}
}

char	*delete_quotes(char *args, char *tmp)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	del_qt_loop(&i, &k, args, tmp);
	tmp[k] = '\0';
	return (tmp);
}

char	**expand_quotes(char **args)
{
	int		i;
	int		count;
	char	*tmp;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		count = count_quotes(args[i]);
		if (!count)
		{
			i++;
			continue ;
		}
		tmp = malloc(sizeof(char) * count + 1);
		if (!tmp)
			return (NULL);
		tmp = delete_quotes(args[i], tmp);
		free (args[i]);
		args[i] = tmp;
		i++;
	}
	return (args);
}

char	**reset_expanded_quotes(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == 5)
				args[i][j] = '\'';
			else if (args[i][j] == 6)
				args[i][j] = '"';
			j++;
		}
		i++;
	}
	return (args);
}
