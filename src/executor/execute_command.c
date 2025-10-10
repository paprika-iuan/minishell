/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:43:13 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/03 09:43:15 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

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

void	cleanup_child(char *full_path, char **env_arr, t_NodeAST *node)
{
	int	i;

	if (full_path)
		free(full_path);
	i = 0;
	if (env_arr)
	{
		while (env_arr[i])
			free(env_arr[i++]);
		free(env_arr);
	}
	if (node)
		free_ast(node);
}

int	execute_cmd(t_NodeAST *node, t_env *env)
{
	char	*full_path;
	char	**env_arr;

	env_arr = NULL;
	full_path = set_cmd_path(node, env);
	if (!full_path)
	{
		printf("command not found\n");
		cleanup_child(full_path, env_arr, node);
		return (COMMAND_NOT_FOUND);
	}
	env_arr = env_converter(env);
	if (!env_arr)
		return (free(full_path), MALLOC_FAILED);
	execve(full_path, node->cmd.args, env_arr);
	cleanup_child(full_path, env_arr, node);
	perror("execve");
	return (COMMAND_NOT_EXECUTABLE);
}

int	execute_one_command(t_NodeAST *node, t_env *env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	// CHECK BUILT INT
	pid = fork();
	if (pid < 0)
		return (perror("fork"), FORK_FAILED);
	if (pid == 0)
	{
		//do_redirections(node);
		exit(execute_cmd(node, env));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), WAITPID_FAILED);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		printf("Parent received exit code: %d\n", exit_code); // Debug
	}
	else
		exit_code = ERROR;
	return (exit_code);
}

// int	execute_builtin(t_NodeAST *node, t_env *env)
// {
// 	return ();
// }

int	execute_command(t_NodeAST *node, t_env *env)
{
	// if builtin ...
	return (execute_cmd(node, env));
}
