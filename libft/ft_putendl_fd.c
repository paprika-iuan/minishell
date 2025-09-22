/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:23:46 by amarquez          #+#    #+#             */
/*   Updated: 2025/05/20 10:23:48 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	length;

	if (s == NULL)
		return ;
	length = 0;
	while (s[length] != '\0')
	{
		ft_putchar_fd(s[length], fd);
		length++;
	}
	ft_putchar_fd('\n', fd);
}
