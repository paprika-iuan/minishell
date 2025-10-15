/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:19:12 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/13 18:18:19 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

int	find_dollar(char *args, char n, int i)
{
	int		dollar;
	int		count;

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

int	find_closure(char *args, char n, int i)
{
	int		close;
	int		count;

	count = 0;
	while (args[i] && count < 2)
	{
		if (args[i] == n)
		{
			count++;
			close = i;
		}
		i++;
	}
	if (count == 2)
		return (close);
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
			if (find_dollar(args, '\'', i))
				return (1);
			j = find_closure(args, '\'', i);
			if (j)
				i = j + 1;
			else
				i++;
			continue ;
		}
		else if (args[i] == '\"')
		{
			if (find_dollar(args, '\"', i))
				return (2);
			j = find_closure(args, '\"', i);
			if (j)
				i = j + 1;
			else
				i++;
			continue ;
		}
		i++;
	}
	return (3);
}

int	expansion_type(char *args)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;

	res = set_exp_type(args, i, j);
	return (res);
}

int	count_var_len(char *args, int start)
{
	int		var_len;

	var_len = 0;
	while (args[start + var_len] && (ft_isalnum(args[start +
			var_len]) || args[start + var_len] == '_'))
		var_len++;
	return (var_len);
}
