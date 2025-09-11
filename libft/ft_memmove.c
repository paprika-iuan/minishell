/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:45:38 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/12 10:45:40 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*sc;

	if (n == 0 || dest == src)
		return (dest);
	dt = (unsigned char *) dest;
	sc = (unsigned char *) src;
	if (dt > sc && dt < sc + n)
	{
		dt += n;
		sc += n;
		while (n--)
			*--dt = *--sc;
	}
	else
	{
		while (n--)
			*dt++ = *sc++;
	}
	return (dest);
}
