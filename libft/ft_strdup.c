/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:17:40 by frafal            #+#    #+#             */
/*   Updated: 2022/10/31 14:33:41 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	if (s == NULL)
	{
		dup = (char *)malloc(sizeof (char));
		dup[0] = '\0';
		return (dup);
	}
	size = (ft_strlen(s) + 1) * sizeof(char);
	dup = (char *)malloc(size);
	if (!dup)
		return (NULL);
	ft_memmove(dup, s, size);
	return (dup);
}
