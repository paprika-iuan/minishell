/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:43:13 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 16:51:34 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

char	**env_converter(t_env *env)
{
	int		size;
	char	**env_arr;
	int		i;

	size = env_list_size(env);
	env_arr = malloc((size + 1) * sizeof(char *));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_arr[i] = ft_strdup(env->content);
		if (!env_arr[i])
		{
			while (i > 0)
				free(env_arr[--i]);
			free(env_arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	update_node_args(t_NodeAST *node, t_env *env)
{
	char	**tmp;

	tmp = expand(node->cmd.args, env);
	tmp = expand_quotes(tmp);
	tmp = reset_expanded_quotes(tmp);
	node->cmd.args = tmp;
}

int	execute_cmd(t_NodeAST *node, t_env *env)
{
	char	*full_path;
	char	**env_arr;

	if (!node->cmd.args)
		return (ERROR);
	env_arr = NULL;
	update_node_args(node, env);
	full_path = set_cmd_path(node, env);
	if (!full_path)
	{
		ft_putstr_fd("wanghao: ", STDERR_FILENO);
		ft_putstr_fd(node->cmd.args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		cleanup_child(full_path, env_arr);
		return (COMMAND_NOT_FOUND);
	}
	env_arr = env_converter(env);
	if (!env_arr)
		return (free(full_path), MALLOC_FAILED);
	execve(full_path, node->cmd.args, env_arr);
	cleanup_child(full_path, env_arr);
	perror("execve");
	return (COMMAND_NOT_EXECUTABLE);
}

int	execute_one_command(t_NodeAST *node, t_env **env_ref)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	t_env	*env;

	env = *env_ref;
	if (is_builtin(node))
		return (exec_builtin_with_redirections(node, env_ref));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), FORK_FAILED);
	if (pid == 0)
	{
		if (!do_redirections(node->cmd.redirect, env))
			exit(ERROR);
		exit(execute_cmd(node, env));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), WAITPID_FAILED);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = ERROR;
	return (exit_code);
}

int	execute_command(t_NodeAST *node, t_env **env_ref)
{
	if (is_builtin(node))
		return (exec_builtin_with_redirections(node, env_ref));
	return (execute_cmd(node, *env_ref));
}
