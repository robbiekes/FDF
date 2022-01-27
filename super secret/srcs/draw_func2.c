/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:10 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/27 14:55:54 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(char *map, t_map *map_data)
{
	int	i;

	i = 0;
	if (!get_height(map) || !get_width(map))
	{
		free(map_data);
		exit(0);
	}
	map_data->height = get_height(map);
	map_data->width = get_width(map);
	map_data->z_matrix = (int **)malloc(sizeof(int *) * map_data->height);
	map_data->colours = (int **)malloc(sizeof(int *) * map_data->height);
	if (!(map_data->z_matrix))
		exit(0);
	while (i < map_data->height)
	{
		map_data->z_matrix[i] = (int *)malloc(sizeof(int) * map_data->width);
		map_data->colours[i] = (int *)malloc(sizeof(int) * map_data->width);
		i++;
	}
	fill_matrix(map_data, map);
}

void	draw_map(t_map *map_data, t_point *p, t_point *p1)
{
	shift_dot(&(*p), map_data);
	shift_dot(&(*p1), map_data);
	draw_line(&(*p), &(*p1), map_data->img, map_data->colour);
}

void	view_above(t_map *map_data, t_data *data, int x, int y)
{
	t_point	p;
	t_point	p1;

	while (++y < map_data->height)
	{
		x = -1;
		while (++x < map_data->width)
		{
			change_x_y(map_data, x, y, &p);
			//map_data->colour = map_data->colours[y][x];
				//map_data->colour = 0xfbf00f0;
			if (x < map_data->width - 1)
			{
				change_x1(map_data, x, y, &p1);
				if (y == 0 && x + 1 > 0)
					map_data->colour = 0x0000ff;
				else 
					map_data->colour = map_data->colours[y][x];
				if (y == map_data->height - 1 && x + 1 > 0)
					map_data->colour = 0x0000ff;
				draw_map(map_data, &p, &p1);
			}
			if (y < map_data->height - 1)
			{
				map_data->colour = 0xfbf00f0;
				change_x_y(map_data, x, y, &p);
				change_y1(map_data, x, y, &p1);
				if ((x == 0 && y + 1 > 0) || (x == map_data->width - 1 && y + 1 > 0))
					map_data->colour = 0x0000ff;
				draw_map(map_data, &p, &p1);
			}
		}
	}
}

void	isometric_map(t_map *map, t_data *data, int i)
{
	t_point	p;
	t_point	p1;
	int		w;

	w = map->width;
	while (++i < map->height * w)
	{
		change_x_y(map, i % w, i / w, &p);
		map->colour = map->colours[i / w][i % w];
		if (i % w < w - 1)
		{
			change_x1(map, i % w, i / w, &p1);
			if (i / w == 0 && (i % w) + 1 > 0)
				map->colour = 0x0000ff;
			else 
				map->colour = map->colours[i / w][i % w];
			if (i / w == map->height - 1 && (i % w) + 1 > 0)
				map->colour = 0x0000ff;
			isom(&p, (map->z_matrix[i / w][i % w] * map->zoom / 2));
			isom(&p1, (map->z_matrix[i / w][i % w + 1] * map->zoom / 2));
			draw_map(map, &p, &p1);
		}
		if (i / w < map->height - 1)
		{
			map->colour = map->colours[i / w][i % w];
			change_x_y(map, i % w, i / w, &p);
			change_y1(map, i % w, i / w, &p1);
			if ((i % w == 0 && (i / w) + 1 > 0) || (i % w == w - 1 && (i / w) + 1 > 0))
					map->colour = 0x0000ff;
			isom(&p, (map->z_matrix[i / w][i % w] * map->zoom / 2));
			isom(&p1, (map->z_matrix[i / w + 1][i % w] * map->zoom / 2));
			draw_map(map, &p, &p1);
		}
	}
}

void	background(t_map *map_data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{	
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(map_data->img, x, y, 0x00001122);
			x++;
		}
		y++;
	}
}
