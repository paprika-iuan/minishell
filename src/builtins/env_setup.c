/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:45:05 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 12:45:07 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	append_env_node(t_env **head, t_env **current, char *content)
{
	t_env	*node;

	node = create_env_node(content);
	if (!node)
		return (0);
	if (!*head)
		*head = node;
	else
		(*current)->next = node;
	*current = node;
	return (1);
}

t_env	*envcpy(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	if (envp && *envp)
	{
		while (envp[i])
		{
			if (!append_env_node(&head, &current, envp[i]))
				return (free_env_list(head), NULL);
			i++;
		}
	}
	else
	{
		if (!append_env_node(&head, &current, ""))
			return (free_env_list(head), NULL);
	}
	return (head);
}

void	add_shlvl(t_env *env)
{
	int		lvl;
	char	*lvl_char;
	char	*shlvl_str;

	shlvl_str = get_env_value("SHLVL", env);
	if (!shlvl_str)
	{
		set_env_value("SHLVL", "1", env);
		return ;
	}
	lvl = ft_atoi(shlvl_str);
	if (!lvl || lvl < 0)
		lvl = 0;
	if (lvl >= 1000)
	{
		ft_putstr_fd("wanghao: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(lvl, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1", STDERR_FILENO);
		lvl = 1;
	}
	else
		lvl++;
	lvl_char = ft_itoa(lvl);
	set_env_value("SHLVL", lvl_char, env);
	free(lvl_char);
}
