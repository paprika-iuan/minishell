/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:19:12 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:19:46 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	find_dollar(char *args, char n)
{
	int		i;
	int		dollar;
	int		count;

	i = 0;
	count = 0;
	dollar = 0;
	while (args[i] && count < 2)
	{
		if (args[i] == '$')
			dollar++;
		if (args[i] == n)
			count++;
		i++;
	}
	if (dollar && count == 2)
		return (i);
	else
		return (0);
}

int	find_closure(char *args, char n)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i] && count < 2)
	{
		if (args[i] == n)
			count++;
		i++;
	}
	if (count == 2)
		return (i);
	else
		return (0);
}

int	set_exp_type(char *args, int i, int j)
{
	while (args[i])
	{
		if (args[i] == '$')
			return (0);
		else if (args[i] == '\'')
		{
			if (find_dollar(args, '\''))
				return (1);
			j = find_closure(args, '\'');
			if (j)
				i = j + 1;
			continue ;
		}
		else if (args[i] == '\"')
		{
			if (find_dollar(args, '\"'))
				return (2);
			j = find_closure(args, '\"');
			if (j)
				i = j + 1;
			continue ;
		}
		i++;
	}
	return (3);
}

int	set_possible_exp(char *args)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = set_exp_type(args, i, j);
	return (res);
}
