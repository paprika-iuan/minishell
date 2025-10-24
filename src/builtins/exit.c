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

#include "../../inc/parser.h"

long	handle_exit_argument(char *arg)
{
	if (!is_valid_long(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	return (ft_atol(arg));
}

int	ft_exit(char **args, t_env *env, t_NodeAST *node)
{
	long	exit_status;

	printf("exit\n");
	if (args[1] && ft_isnumeric(args[1]) && args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), ERROR);
	if (args[1])
		exit_status = handle_exit_argument(args[1]);
	else
	{
		if (!get_env_value("LAST_EXIT", env))
			exit_status = 0;
		else
			exit_status = ft_atol(get_env_value("LAST_EXIT", env));
	}
	if (node)
		free_ast(node);
	if (env)
		free_env_list(env);
	exit(exit_status);
	return (ERROR);
}
