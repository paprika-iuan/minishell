/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:36:30 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/26 14:36:32 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_pwd_error(t_env *env)
{
	char	*env_pwd;

	if (errno == ENOENT)
	{
		env_pwd = get_env_value("PWD", env);
		if (env_pwd)
		{
			printf("%s\n", env_pwd);
			return (0);
		}
	}
	perror("pwd");
	return (ERROR);
}

int	ft_pwd(char **argv, t_env *env)
{
	char	pwd[PATH_MAX];

	if (argv && argv[1])
	{
		ft_printf("pwd: too many arguments\n");
		return (ERROR);
	}
	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		return (0);
	}
	return (handle_pwd_error(env));
}
