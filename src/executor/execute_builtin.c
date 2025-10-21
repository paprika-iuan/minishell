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

	if (node->cmd.args)
	{
		name = node->cmd.args[0];
		if (!name)
			return (FAILURE);
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
	}
	return (FAILURE);
}

int	execute_builtin(t_NodeAST *node, t_env *env)
{
	char	*name;

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
		return (ft_env(node->cmd.args, env));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd(node->cmd.args, env));
	return (ERROR);
}

int	exec_builtin_with_redirections(t_NodeAST *node, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!do_redirections(node->cmd.redirect))
		return (close(saved_stdin), close(saved_stdout), ERROR);
	ret = execute_builtin(node, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}
