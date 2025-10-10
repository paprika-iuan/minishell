/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_ifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:23:43 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:20:29 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	is_ifs(char c, t_env *env)
{
	char	*ifs;
	int		i;

	i = 0;
	ifs = (get_env_value("IFS", env));
	if (!ifs)
		ifs = " \t\n";
	while (ifs[i])
	{
		if (c == ifs[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_ifs_tokens(char *args, char ifs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == ifs)
			count++;
		else
		{
			while (args[i] && args[i] != ifs)
				i++;
			count++;
		}
	}
	return (count);
}

void	set_empty_str(char **res, int *i, int *c)
{
	res[*c] = malloc(1);
	if (!res[*c])
		return ;
	res[*c][0] = '\0';
	(*c)++;
	(*i)++;
}

void	set_ifs_str(char *args, char ifs, char **res, int *c)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == ifs)
			set_empty_str(res, &i, &c);
		else
		{
			start = i;
			while (args[i] && args[i] != ifs)
				i++;
			res[*c] = ft_substr(args, start, i - start);
			if (!res[*c])
				return ;
			(*c)++;
		}
	}
}

char	**do_ws_ifs(char *args, char ifs)
{
	int		c;
	char	**res;

	c = 0;
	c = count_ifs_tokens(args, ifs);
	res = malloc(sizeof(char *) * (c + 1));
	if (!res)
		return (NULL);
	c = 0;
	set_ifs_str(args, ifs, res, &c);
	res[c] = NULL;
	return (res);
}
