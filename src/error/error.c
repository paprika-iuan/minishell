/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:12:27 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/20 16:12:29 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_last_error(t_mini *mini)
{
	return (mini->last_error);
}

void	set_last_error(int error, t_mini *mini)
{
	mini->last_error = error;
}
