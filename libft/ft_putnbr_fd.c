/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:21:24 by frafal            #+#    #+#             */
/*   Updated: 2022/10/11 16:55:22 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr(long n, int fd)
{
	char	c;

	if (n == 0)
		return ;
	ft_printnbr(n / 10, fd);
	c = n % 10 + '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	abs_val;

	abs_val = n;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
	{
		abs_val = (-1) * abs_val;
		write(fd, "-", 1);
	}
	ft_printnbr(abs_val, fd);
}
