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

int	ft_exit(char **args, t_env *env, t_NodeAST *node)
{
	int	exit_status;

	printf("exit\n");
	if (args[1] && ft_isnumeric(args[1]) && args[2])
		return (printf("exit: too many arguments\n"), ERROR);
	if (args[1])
	{
		if (ft_isnumeric(args[1]))
			exit_status = (ft_atoi(args[1]));
		else
			exit_status = 2;
	}
	else
	{
		if (!get_env_value("LAST_EXIT", env))
			exit_status = 0;
		else
			exit_status = ft_atoi(get_env_value("LAST_EXIT", env));
	}
	if (node)
		free_ast(node);
	if (env)
		free_env_list(env);
	exit(exit_status);
	return (ERROR);
}
