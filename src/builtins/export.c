/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:48:07 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/23 15:36:36 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	var_printer(t_env *current)
{
	char	*eq;

	while (current)
	{
		eq = ft_strchr(current->content, '=');
		if (eq)
		{
			write(1, "declare -x ", 12);
			write(1, current->content, eq - current->content);
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"\n", 2);
		}
		else
			printf("declare -x %s\n", current->content);
		current = current->next;
	}
}

int	export_arg_checker(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) && args[i] != '_')
	{
		printf("export: %s: invalid identifier\n", args);
		return (1);
	}
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
		{
			printf("export: %s: not a valid identifier\n", args);
			return (1);
		}
		i++;
	}
	return (0);
}

int	dup_var_handler(char *arg, t_env *env)
{
	int		len;
	t_env	*iter;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	iter = env;
	while (iter)
	{
		if (!ft_strncmp(arg, iter->content, len)
			&& (iter->content[len] == '=' || iter->content[len] == '\0'))
		{
			free(iter->content);
			iter->content = ft_strdup(arg);
			if (!iter->content)
				return (0);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

int	handle_export_arg(char *arg, t_env *env)
{
	t_env	*new_node;
	char	*dup;

	if (export_arg_checker(arg))
		return (0);
	if (!dup_var_handler(arg, env))
	{
		dup = ft_strdup(arg);
		if (!dup)
			return (1);
		new_node = create_env_node(dup);
		if (!new_node)
		{
			free(dup);
			return (1);
		}
		add_to_env_list(env, new_node);
		free(dup);
	}
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int	i;

	if (!args[1])
		return (var_printer(env), 0);
	i = 1;
	while (args[i])
	{
		handle_export_arg(args[i], env);
		i++;
	}
	return (0);
}
