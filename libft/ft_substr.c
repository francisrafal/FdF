/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:30:40 by frafal            #+#    #+#             */
/*   Updated: 2022/10/13 13:02:06 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;

	if (s == NULL)
		return (NULL);
	substr_len = 0;
	while (start < ft_strlen(s) && s[substr_len + start] && substr_len < len)
		substr_len++;
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr[0] = '\0';
		return (substr);
	}
	ft_memmove(substr, s + start, substr_len + 1);
	substr[substr_len] = 0;
	return (substr);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *str = strdup("1");
	char *s = ft_substr(str, 42, 42000000);
	printf("\"%s\"\n", s);
	free(s); free(str); 
	return (0);
}
*/
