/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:12:35 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/26 21:18:06 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point *p, t_point *p1, t_data *data, int colour)
{
	float	x_step;
	float	y_step;
	int		max;

	x_step = p1->x - p->x;
	y_step = p1->y - p->y;
	max = ft_max(ft_abs(x_step), ft_abs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(p->x - p1->x) || (int)(p->y - p1->y))
	{
		if (p->x >= 0 && p->x < HEIGHT && p->y >= 0 && p->y < WIDTH)
			my_mlx_pixel_put(data, (int)p->x, (int)p->y, colour);
		p->x += x_step;
		p->y += y_step;
	}
}

int	get_height(char *file)
{
	int		strings;
	char	*line;
	int		fd;

	strings = 0;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = 0;
		strings++;
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (strings);
}

int	get_width(char *file)
{
	int		fd;
	char	*string;
	char	**splitted_str;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	string = get_next_line(fd);
	if (string)
	{
		splitted_str = ft_split(string, ' ');
		if (!splitted_str)
			finish(0);
		free(string);
	}
	while (string)
	{
		string = get_next_line(fd);
		if (string)
			free(string);
	}
	close(fd);
	return (ft_ptrlen(splitted_str));
}

void	fill_colours(t_map *map_data, char **str, int i)
{
	int		j;
	char	**substr;

	j = 0;
	while (j < map_data->width)
	{
		substr = ft_split(str[j], ',');
		if (substr[1] != 0)
			map_data->colours[i][j] = ft_atoi_base(&(substr[1][2]),
					"0123456789ABCDEF");
		else
			map_data->colours[i][j] = 0xfbf00f0;
		j++;
		free_splitted_exit(substr, 0);
	}
}

void	fill_matrix(t_map *map_data, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*string;
	char	**splitted_str;

	fd = open(file, O_RDONLY, 0);
	i = 0;
	j = 0;
	while (i < map_data->height)
	{
		string = get_next_line(fd);
		splitted_str = ft_split(string, ' ');
		fill_colours(map_data, splitted_str, i);
		j = 0;
		while (j < map_data->width)
		{
			map_data->z_matrix[i][j] = ft_atoi(splitted_str[j]);
			j++;
		}
		free_splitted_exit(splitted_str, 0);
		free(string);
		i++;
	}
	close(fd);
}
