/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:07:06 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 18:37:28 by jgirbau-         ###   ########.fr       */
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

char	*do_env_var(t_mini *mini, char *to_expand)
{
	char	*env_var;
	char	*env_var_tmp;

	if (ft_strcmp(to_expand, "?") == 0)
		env_var = ft_itoa(get_last_error(mini));
	else
	{
		env_var_tmp = get_env_value(to_expand, mini->env);
		if (env_var_tmp)
			env_var = ft_strdup(env_var_tmp);
		else
			env_var = NULL;
	}
	return (env_var);
}

char	*dollar_expanded(char *args, t_mini *mini)
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
	env_var = do_env_var(mini, to_expand);
	if (!env_var)
		return (free(to_expand), NULL);
	res = ft_strdup(env_var);
	if (!res)
		res = "";
	if (res)
		return (free(env_var), free (to_expand), respect_quotes_mini(res),
			res);
	return (free(env_var), free(to_expand), free(res), NULL);
}
