/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:39:08 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 11:39:09 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_spaces_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	is_valid_long(const char *str)
{
	long	result;
	int		sign;
	int		i;
	int		digit;

	result = 0;
	i = skip_spaces_and_sign(str, &sign);
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (sign == 1 && (result > (LONG_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (-result < (LONG_MIN + digit) / 10))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}
