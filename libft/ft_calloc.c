/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:37 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/14 17:25:39 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char		*pt;

	if (nmemb != 0 && size > (size_t)(-1) / nmemb)
		return (NULL);
	pt = malloc(nmemb * size);
	if (pt == NULL)
		return (NULL);
	ft_memset(pt, 0, nmemb * size);
	return (pt);
}
