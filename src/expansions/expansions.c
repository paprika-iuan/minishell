/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:15:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:19:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	find_end_var(char *args)
{
	int	i;

	i = 0;
	while (args[len] && args[i] != '$')
		i++;
	while (args[i] && (ft_isalnum(args[i]) || args[i] == '_'))
	{
		if (args[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*find_n(int *n)
{
	int	i;

	i = 0;
	if (n[i] == 0)
		return ('$');
	else if (n[i] == 1)
		return ('\'');
	else if (n[i] == 2)
		return ('\"');
}

char	**expand(char **args, t_env *env)
{
	int	n;
	int	i;

	i = 0;
	while (args[i])
	{
		n = set_possible_exp(args[i]);
		if (n == 3)
			return (args);
		if (n == 2)
			do_doublequote(args, i, env);
		if (n == 1)
			do_singlequote(args, i, env);
		if (n == 0)
			args = do_just_expansion(args, i, env);
		i++;
	}
	return (args);
}
