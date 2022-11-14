/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:21 by frafal            #+#    #+#             */
/*   Updated: 2022/11/11 10:45:16 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	arr_size;

	if (size > 4294967294 || nmemb > 4294967294)
		return (NULL);
	arr_size = nmemb * size;
	if (arr_size > 2147483647)
		return (NULL);
	arr = malloc(arr_size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, arr_size);
	return (arr);
}
