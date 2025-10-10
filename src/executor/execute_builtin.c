/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:30 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/08 16:41:32 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	is_builtin(t_NodeAST *node)
{
	char	*name;

	name =  node->cmd.args[0];
	if (ft_strcmp(name, "cd") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "export") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "unset") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "exit") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "echo") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "env") == 0)
		return (SUCCESS);
	if (ft_strcmp(name, "pwd") == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	execute_builtin(t_NodeAST *node, t_env *env)
{
	char	*name;

	// do redirections
	name = node->cmd.args[0];
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(node->cmd.args, env));
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(node->cmd.args, env));
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(node->cmd.args, env));
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(node->cmd.args, env, node));
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(node->cmd.args));
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(env));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd(node->cmd.args));
	return (ERROR);
}
