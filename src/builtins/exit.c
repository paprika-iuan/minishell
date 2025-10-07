/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:22:08 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/26 16:22:13 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_env *env, char **args)
{
	ft_printf("exit\n");
	if (args && args[1])
	{
		ft_printf("exit: too many arguments\n");
		return ;
	}
	if (env)
		free_env_list(env);
	exit(0);
}
