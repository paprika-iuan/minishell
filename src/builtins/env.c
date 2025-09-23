/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:50:04 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 10:40:50 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env(t_env *cp_env)
{
	basic_err(cp_env->content);
	while (cp_env)
	{
		if (ft_strchr(cp_env->content, '='))
			printf("%s\n", cp_env->content);
		cp_env = cp_env->next;
	}
	return (0);
}
