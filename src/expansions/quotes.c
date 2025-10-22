/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:39:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/20 16:50:53 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

int	count_quotes(char *args)
{
	int	i;
	int	count;

	if (!args)
		return (0);
	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
			count++;
		i++;
	}
	return (count);
}

char	*delete_quotes(char *args, char *tmp)
{
	int	i;
	int	k;

	if (!args)
		return (NULL);
	i = 0;
	k = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			i++;
			continue ;
		}
		tmp[k++] = args[i++];
	}
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
		count = ft_strlen(args[i]) - count_quotes(args[i]);
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
