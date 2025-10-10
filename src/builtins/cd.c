/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:38:52 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/23 11:38:53 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*resolve_cd_path(char **args, t_env *env)
{
	char	*path;

	if (!args[1] || (args[1][0] == '~' && !args[1][1]))
	{
		path = get_env_value("HOME", env);
		if (!path)
			perror("cd: HOME not set");
	}
	else if (args[1][0] == '-')
	{
		path = get_env_value("OLDPWD", env);
		if (!path)
			perror("cd: OLDPWD not set");
		else
			printf("%s\n", path);
	}
	else
		path = args[1];
	return (path);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;
	char	oldpath[PATH_MAX];
	char	currpath[PATH_MAX];

	if (args[1] && args[2])
		return (printf("cd: too many arguments\n"), ERROR);
	path = resolve_cd_path(args, env);
	if (!path)
		return (ERROR);
	if (!getcwd(oldpath, sizeof(oldpath)))
		return (perror("cd: getcwd"), ERROR);
	if (chdir(path) != 0)
		return (perror("cd"), ERROR);
	if (set_env_value("OLDPWD", oldpath, env) == -1)
		return (ERROR);
	if (!getcwd(currpath, sizeof(currpath)))
		return (perror("cd: getcwd"), ERROR);
	if (set_env_value("PWD", currpath, env) == -1)
		return (ERROR);
	return (0);
}
