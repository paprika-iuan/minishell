/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:13:50 by amarquez          #+#    #+#             */
/*   Updated: 2025/06/17 16:13:52 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	conversor(const char *type, va_list vargs)
{
	char	*dec;
	char	*hex_l;
	char	*hex_u;

	dec = "0123456789";
	hex_l = "0123456789abcdef";
	hex_u = "0123456789ABCDEF";
	if (*type == 'c')
		return (ft_printchar(va_arg(vargs, int)));
	else if (*type == 's')
		return (ft_printstr(va_arg(vargs, char *)));
	else if (*type == 'i' || *type == 'd')
		return (ft_printnbr_base(va_arg(vargs, int), dec));
	else if (*type == 'u')
		return (ft_printnbr_base_u(va_arg(vargs, unsigned int), dec));
	else if (*type == 'x')
		return (ft_printnbr_base_u(va_arg(vargs, unsigned int), hex_l));
	else if (*type == 'X')
		return (ft_printnbr_base_u(va_arg(vargs, unsigned int), hex_u));
	else if (*type == 'p')
		return (ft_printptr(va_arg(vargs, void *), hex_l));
	else if (*type == '%')
		return (ft_printchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		total_count;

	va_start(args, str);
	total_count = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1) && ft_strchr("csiduxXp%", *++str))
		{
			total_count += conversor(str, args);
			str++;
		}
		else
		{
			total_count += ft_printchar(*str);
			++str;
		}
	}
	va_end(args);
	return (total_count);
}
/*
#include <stdio.h>
#include <limits.h>

int main() {

    printf("%c %c %c\n" , 'a', 'b', 'c');
    ft_printf("%c %c %c\n" , 'a', 'b', 'c');

    printf("%s\n", "Electric bogaloo");
    ft_printf("%s\n", "Electric bogaloo");

    printf("%d\n", 12455);
    ft_printf("%d\n", 12455);

    printf("%i\n", -7133);
    ft_printf("%i\n", -7133);

    printf("%u\n", 65416u);
    ft_printf("%u\n", 65416u);

    int a = 3;
    int *ptr = &a;
    void *ptrv = NULL;
    printf("%p\n %p\n", ptr, ptrv);
    ft_printf("%p\n %p\n", ptr, ptrv);

    printf("Percent: %%\n");
    ft_printf("Percent: %%\n");

    printf("\n=== EDGE CASES ===\n");

    printf(" NULL %s NULL ", NULL);
    ft_printf(" NULL %s NULL ", NULL);

    printf("Empty string: [%s]\n", "");
    ft_printf("Empty string: [%s]\n", "");

    printf("INT_MAX: %d\n", INT_MAX);
    ft_printf("INT_MAX: %d\n", INT_MAX);

    printf("INT_MIN: %d\n", INT_MIN);
    ft_printf("INT_MIN: %d\n", INT_MIN);

    printf("Zero: %d\n", 0);
    ft_printf("Zero: %d\n", 0);

    printf("-1: %d\n", -1);
    ft_printf("-1: %d\n", -1);

    // Unsigned limits
    printf("UINT_MAX: %u\n", UINT_MAX);
    ft_printf("UINT_MAX: %u\n", UINT_MAX);

    printf("Zero unsigned: %u\n", 0u);
    ft_printf("Zero unsigned: %u\n", 0u);


    printf("HEX UINT_MAX: %X\n", UINT_MAX);
    ft_printf("HEX UINT_MAX: %X\n", UINT_MAX);

    // Pointer edge cases
    printf("Pointer to stack: %p\n", &a);
    ft_printf("Pointer to stack: %p\n", &a);

    printf("NULL pointer: %p\n", (void*)NULL);
    ft_printf("NULL pointer: %p\n", (void*)NULL);

    printf("Pointer to 0: %p\n", (void*)0);
    ft_printf("Pointer to 0: %p\n", (void*)0);

    printf("\n=== MIXED FORMAT TESTS ===\n"

    return 0;

}
*/
