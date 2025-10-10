/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:07:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:19:52 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

char	*set_after_dollar(char *args)
{
	int		start;
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	start = find_end_var(args);
	if (!start)
		return (NULL);
	i = start;
	while (args[i])
	{
		len++;
		i++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (args[start])
		res[i++] = args[start++];
	res[i] = '\0';
	return (res);
}

char	*set_before_dollar(char *args)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	while (args[len] && args[len] != '$')
		len++;
	if (!len)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len)
		res[i] = args[i];
	res[i] = '\0';
	return (res);
}

char	*dollar_expanded(char *args, t_env *env)
{
	char	*dollar_pos;
	char	*to_expand;
	int		var_len;
	char	*res;

	dollar_pos = ft_strchr(args, '$');
	if (!dollar_pos)
		return (NULL);
	var_len = count_var_len(dollar_pos, 1);
	if (!var_len)
		return (NULL);
	to_expand = ft_substr(dollar_pos, 1, var_len);
	if (!to_expand)
		return (NULL);
	res = get_env_value(to_expand, env);
	free (to_expand);
	if (res)
		return (ft_strdup(res));
	return (NULL);
}

int	ft_arraylen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static char	**free_result(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
	return (NULL);
}
