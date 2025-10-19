/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:18:56 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/03 13:04:30 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_signal_value = 0;

void	sig_int_c(int sign)
{
	printf("\n[DEBUG sig_int_c] rl_done=%d, rl_point=%d, rl_end=%d, rl_already_prompted=%d\n",
		rl_done, rl_point, rl_end, rl_already_prompted);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_value = sign;
	//printf("sign: %i", g_signal_value);
	// last_error = 128 + g_signal_num
}

void	sig_nonint_c(int sign)
{
	printf("\n");
	rl_on_new_line();
	g_signal_value = sign;
}

void	signals_intmode(void)
{
	signal(SIGINT, sig_int_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_nonintmode(void)
{
	signal(SIGINT, sig_nonint_c);
	signal(SIGQUIT, sig_nonint_c);
}
