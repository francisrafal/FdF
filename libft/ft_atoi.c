/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:14:08 by frafal            #+#    #+#             */
/*   Updated: 2022/10/12 11:33:50 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	over_llong(long long i, int sign, int digits, const char *nptr)
{
	char	*llong_max_abs;
	char	*llong_min_abs;

	llong_max_abs = "9223372036854775807";
	llong_min_abs = "9223372036854775808";
	if (sign == 1)
	{
		if (digits > 19)
			return (-1);
		if (digits == 19 && (ft_strncmp(&nptr[i - 19], llong_max_abs, 19) > 0))
			return (-1);
	}
	if (sign == -1)
	{
		if (digits > 19)
			return (0);
		if (digits == 19 && (ft_strncmp(&nptr[i - 19], llong_min_abs, 19) > 0))
			return (0);
	}
	return (1);
}

static void	trim_space_and_sign(long long *i, int *sign, const char *nptr)
{
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	if (nptr[*i] == '+' && *sign != -1)
		(*i)++;
}

int	ft_atoi(const char *nptr)
{
	long long			i;
	int					sign;
	int					digits;
	unsigned long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	digits = 0;
	trim_space_and_sign(&i, &sign, nptr);
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i++] - 48);
		digits++;
	}
	digits = over_llong(i, sign, digits, nptr);
	if (digits <= 0)
		return (digits);
	return (nb * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	int	x;
	int	y;
	char	*nptr = av[1];
	if (ac == 2)
	{
		x = ft_atoi(av[1]);
		printf("Input:  %s\n", av[1]);
		printf("Output mine:  %d\n", x);
	
		y = atoi(nptr);
		printf("Input:  %s\n", nptr);
		printf("Output atoi:  %d\n", y);
	}
	return (0);
}
*/
