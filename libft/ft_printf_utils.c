/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:12:36 by frafal            #+#    #+#             */
/*   Updated: 2022/11/11 10:58:25 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *str)
{
	int	printed;

	printed = 0;
	if (str == NULL)
		return (print_str("(null)"));
	while (str[printed])
	{
		ft_putchar_fd(str[printed], 1);
		printed++;
	}
	return (printed);
}

char	*u_itoa(unsigned int n)
{
	char			*a;
	int				digits;
	unsigned int	num;

	num = n;
	digits = 1;
	while (num / 10 != 0)
	{
		digits++;
		num /= 10;
	}
	a = (char *)malloc((digits + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	a[digits] = '\0';
	while (digits > 0)
	{
		a[digits - 1] = n % 10 + '0';
		digits--;
		n /= 10;
	}
	return (a);
}

int	print_unsigned(unsigned int n)
{
	int		printed;
	char	*a;

	printed = 0;
	a = u_itoa(n);
	printed += print_str(a);
	free(a);
	return (printed);
}

int	print_nbr(int n)
{
	int		printed;
	char	*a;

	printed = 0;
	a = ft_itoa(n);
	printed += print_str(a);
	free(a);
	return (printed);
}

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
