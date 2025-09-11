/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:44:10 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/12 12:19:28 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*sc;

	if (n == 0)
		return (dest);
	dt = (unsigned char *) dest;
	sc = (unsigned char *) src;
	while (n > 0)
	{
		*dt = *sc;
		dt++;
		sc++;
		n--;
	}
	return (dest);
}
