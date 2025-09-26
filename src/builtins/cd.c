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

char	*resolve_cd_path(char **argv, t_env *env)
{
	char	*path;

	if (!argv[0] || (argv[0][0] == '~' && !argv[0][1]))
	{
		path = get_env_value("HOME", env);
		if (!path)
			perror("cd: HOME not set");
	}
	else if (argv[0][0] == '-')
	{
		path = get_env_value("OLDPWD", env);
		if (!path)
			perror("cd: OLDPWD not set");
		else
			ft_printf("%s\n", path);
	}
	else
		path = argv[0];
	return (path);
}

int	ft_cd(t_env *env, char **argv)
{
	char	*path;
	char	oldpath[PATH_MAX];
	char	currpath[PATH_MAX];

	if (argv[0] && argv[1])
		return (ft_printf("cd: too many arguments\n"), 1);
	path = resolve_cd_path(argv, env);
	if (!path)
		return (1);
	if (!getcwd(oldpath, sizeof(oldpath)))
		return (perror("cd: getcwd"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (set_env_value("OLDPWD", oldpath, env) == -1)
		return (1);
	if (!getcwd(currpath, sizeof(currpath)))
		return (perror("cd: getcwd"), 1);
	if (set_env_value("PWD", currpath, env) == -1)
		return (1);
	return (0);
}
