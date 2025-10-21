/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:07:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/21 18:11:18 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/expansion.h"

char	*set_after_dollar(char *args)
{
	int		start;
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	start = find_end_var(args);
	if (!start || !args[start])
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
	i = 0;
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
	{
		res[i] = args[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	respect_quotes_mini(char *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '\'')
			res[i] = 5;
		if (res[i] == '"')
			res[i] = 6;
		i++;
	}
}

char	*dollar_expanded(char *args, t_env *env)
{
	char	*dollar_pos;
	char	*to_expand;
	int		var_len;
	char	*res;
	char	*env_var;

	dollar_pos = ft_strchr(args, '$');
	if (!dollar_pos)
		return (NULL);
	var_len = count_var_len(dollar_pos, 1);
	if (!var_len)
		return (ft_strndup("$", 1));
	to_expand = ft_substr(dollar_pos, 1, var_len);
	if (!to_expand)
		return (NULL);
	env_var = get_env_value(to_expand, env);
	if (!env_var)
		return (free(to_expand), NULL);
	res = ft_strdup(env_var);
	if (!res)
		res = "";
	if (res)
		return (free (to_expand), respect_quotes_mini(res),
			res);
	return (free(to_expand), free(res), NULL);
}

int	ft_arraylen(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}
