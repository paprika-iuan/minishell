/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:12:27 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/20 16:12:29 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_last_error(t_env *env)
{
	t_env	*iter;

	if (!env)
		return (0);
	iter = env;
	while (iter)
	{
		if (ft_isdigit(iter->content[0]))
			return (ft_atoi(iter->content));
		iter = iter->next;
	}
	return (0);
}

void	set_last_error(int error, t_env *env)
{
	t_env	*iter;
	t_env	*error_node;
	t_env	*new_node;
	char	*error_str;

	if (!env)
		return ;
	iter = env;
	error_node = NULL;
	while (iter)
	{
		if (ft_isdigit(iter->content[0]))
		{
			error_node = iter;
			break ;
		}
		iter = iter->next;
	}
	error_str = ft_itoa(error);
	if (!error_str)
		return ;
	if (error_node)
	{
		free(error_node->content);
		error_node->content = error_str;
	}
	else
	{
		new_node = create_env_node(error_str);
		free(error_str);
		if (!new_node)
			return ;
		add_to_env_list(env, new_node);
	}
}
