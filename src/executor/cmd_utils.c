/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:24:04 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/07 15:24:06 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	is_abs_path(const char *cmd_name)
{
	if (cmd_name[0] == '/')
		return (1);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (1);
	if (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/')
		return (1);
	return (0);
}

char	*pathfinder(char **paths, char *cmd_name)
{
	char	*tmp;
	char	*full_path;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd_name);
		if (!full_path)
			return (free(tmp), NULL);
		free(tmp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

char	**set_paths(t_env *env)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		ft_putstr_fd("Error creating paths\n", STDERR_FILENO);
		return (NULL);
	}
	return (paths);
}

char	*set_cmd_path(t_NodeAST *node, t_env *env)
{
	char	**paths;
	char	*cmd_name;
	char	*result;

	cmd_name = node->cmd.args[0];
	if (!cmd_name[0])
		return (NULL);
	if (is_abs_path(cmd_name))
	{
		if (access(cmd_name, F_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	paths = set_paths(env);
	if (!paths)
		return (NULL);
	result = pathfinder(paths, cmd_name);
	free_matrix(paths);
	return (result);
}
