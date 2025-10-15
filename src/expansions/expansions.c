/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:15:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/13 20:07:34 by jgirbau-         ###   ########.fr       */
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
	while (args[i] && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	return (i);
}

int	find_n(int *n)
{
	int	i;

	i = 0;
	if (n[i] == 0)
		return ('$');
	else if (n[i] == 1)
		return ('\'');
	else if (n[i] == 2)
		return ('\"');
	return (3);
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
			 ;
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
