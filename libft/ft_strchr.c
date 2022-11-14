/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:20:08 by frafal            #+#    #+#             */
/*   Updated: 2022/10/31 14:29:51 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] != (char)c))
	{
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + i);
	if (!s[i])
		return (NULL);
	return ((char *)s + i);
}
