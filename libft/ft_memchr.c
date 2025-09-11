/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:58:03 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/14 14:58:04 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*pt;

	pt = (unsigned char *) s;
	while (n > 0)
	{
		if (*pt == (unsigned char)c)
			return (pt);
		pt++;
		n--;
	}
	return (NULL);
}
