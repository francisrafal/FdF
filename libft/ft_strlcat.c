/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:21:34 by frafal            #+#    #+#             */
/*   Updated: 2022/10/05 17:29:13 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;

	d = 0;
	s = 0;
	while (dst[d] != '\0' && d < size)
		d++;
	while ((src[s] != '\0') && (s + d + 1 < size))
	{
		dst[d + s] = src[s];
		s++;
	}
	if (d != size)
		dst[d + s] = '\0';
	return (d + ft_strlen(src));
}
