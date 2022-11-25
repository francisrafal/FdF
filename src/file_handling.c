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

int	count_cols(char *s)
{
	int		cols;
	char	**split;
	char	*tmp;

	tmp = ft_strdup(s);
	cols = 0;
	ft_striteri(tmp, replace_newline);
	split = ft_split(tmp, ' ');
	free(tmp);
	while (split[cols] != NULL)
		cols++;
	free_str_arr(split);
	return (cols);
}

int	parse_file(t_data *data, char *filename)
{
	int		fd;
	char	*file;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to open file\n", 2);
		return (-1);
	}
	data->map = malloc(sizeof(t_map));
	if (data->map == NULL)
		return (-1);
	file = get_file(fd, data);
	if (file == NULL)
		return (-1);
	ft_striteri(file, replace_newline);
	data->parsed_file = ft_split(file, ' ');
	free(file);
	if (close(fd) == -1)
	{
		ft_putstr_fd("Failed to close file\n", 2);
		return (-1);
	}
	return (0);
}
