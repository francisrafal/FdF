/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:07:35 by frafal            #+#    #+#             */
/*   Updated: 2022/11/25 12:07:42 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	replace_newline(unsigned int i, char *s)
{
	(void)i;
	if (*s == '\n')
		*s = ' ';
}

int	print_parsed_file(char **parsed_file)
{
	int	i;

	i = 0;
	while (parsed_file[i] != NULL)
	{
		ft_printf("%s\n", parsed_file[i]);
		i++;
	}
	return (i);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

int		count_cols(char *s)
{
	int	cols;
	char **split;

	cols = 0;
	ft_striteri(s, replace_newline);
	split = ft_split(s, ' ');
	while (split[cols] != NULL)
		cols++;
	free_str_arr(split);
	return (cols);
}