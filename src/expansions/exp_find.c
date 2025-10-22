/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:19:12 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 18:36:45 by jgirbau-         ###   ########.fr       */
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

int	define_quote_type(char *args, int i, char tmp)
{
	int	closure;

	if (find_dollar(args, tmp, i))
	{
		if (tmp == '\'')
			return (1);
		if (tmp == '"')
			return (2);
	}
	closure = find_closure(args, tmp, i);
	return (closure);
}

int	expansion_type(char *args)
{
	int		i;
	int		q_close;
	char	tmp;

	i = 0;
	q_close = 0;
	while (args[i])
	{
		if (args[i] == '$')
			return (0);
		else if (args[i] == '\'' || args[i] == '\"')
		{
			tmp = args[i];
			q_close = define_quote_type(args, i, tmp);
			if (q_close == 1 || q_close == 2)
				return (q_close);
			if (q_close)
				i = q_close + 1;
			else
				i++;
			continue ;
		}
		i++;
	}
	return (3);
}

int	count_var_len(char *args, int start)
{
	int		var_len;

	var_len = 0;
	while (args[start + var_len] && (ft_isalnum(args[start + var_len])
			|| args[start + var_len] == '_' || args[start + var_len] == '?'))
		var_len++;
	return (var_len);
}
