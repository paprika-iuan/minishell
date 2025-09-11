/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:57:30 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/14 14:57:32 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_c;

	last_c = (char *)s + ft_strlen(s);
	while (last_c > s && *last_c != (char)c)
		last_c--;
	if (*last_c == (char)c)
		return (last_c);
	return (NULL);
}
