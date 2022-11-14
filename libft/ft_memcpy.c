/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:07:30 by frafal            #+#    #+#             */
/*   Updated: 2022/10/12 17:03:20 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *) dest;
	s = (char *) src;
	while (n > 0)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
	return (dest);
}
/*

#include <string.h>
#include <stdio.h>
int	main(void)
{
	char *src = NULL;
	char dest[100];
	char dest2[100];
	//char *dest = NULL;
	//char *dest2 = NULL;
	size_t	n = 0;
	char	*res = ft_memcpy(dest2, src, n);
	char	*res2 = memcpy(dest, src, n);
	printf("ft: address: %p, string: \"%s\"\n", res, res);
	printf("original: address: %p, string: \"%s\"\n", res2, res2);
	return (0);
}
*/
