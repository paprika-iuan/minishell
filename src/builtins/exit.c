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

void	ft_exit(t_env *env, char **argv)
{
	ft_printf("exit\n");
	if (argv && argv[0])
	{
		ft_printf("exit: too many arguments\n");
		return ;
	}
	if (env)
		free_env_list(env);
	exit(0);
}
