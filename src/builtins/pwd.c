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

int	ft_pwd(char **argv)
{
	char	pwd[PATH_MAX];

	if (argv && argv[1])
	{
		ft_printf("pwd: too many arguments\n");
		return (1);
	}
	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", pwd);
	return (0);
}
