/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:53:05 by amarquez          #+#    #+#             */
/*   Updated: 2025/06/19 14:53:08 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr_base(int nbr, char *base)
{
	long int	l;
	int			count;

	count = 0;
	l = nbr;
	if (l < 0)
	{
		ft_putchar_fd('-', 1);
		count++;
		l = -l;
	}
	if (l >= (long)ft_strlen(base))
		count += ft_printnbr_base(l / ft_strlen(base), base);
	ft_putchar_fd(base[l % ft_strlen(base)], 1);
	return (count + 1);
}

int	ft_printnbr_base_u(uintptr_t nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr >= ft_strlen(base))
		count += ft_printnbr_base_u(nbr / ft_strlen(base), base);
	ft_putchar_fd(base[nbr % ft_strlen(base)], 1);
	return (count + 1);
}
