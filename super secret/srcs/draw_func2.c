/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:25:10 by mgwyness          #+#    #+#             */
/*   Updated: 2022/02/11 20:21:02 by mgwyness         ###   ########.fr       */
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

int	pick_colour(int x, int y)
{
	int	red, blue, green, colour;
	red = x * 255 / WIDTH;
	blue = ((HEIGHT + WIDTH) - x - y) * 255 / (HEIGHT + WIDTH);
	green = ((WIDTH) - x + y) * 255 / (HEIGHT + WIDTH);
	int somecolour = (red + 2000) * 255 / (HEIGHT + WIDTH);
	
	colour = (green << 16) + (red << 8) + blue;
	return (colour);
}

void	coloured_line(t_point *p, t_point *p1, t_data *data, int colour, int x, int y)
{
	float	x_step;
	float	y_step;
	int		max, tmp;

	x_step = p1->x - p->x;
	y_step = p1->y - p->y;
	max = ft_max(ft_abs(x_step), ft_abs(y_step));
	x_step /= max;
	y_step /= max;
	tmp = colour;
	while ((int)(p->x - p1->x) || (int)(p->y - p1->y))
	{
		tmp = tmp + 0xfafaff;
		if (p->x >= 0 && p->x < WIDTH && p->y >= 0 && p->y < HEIGHT)
			my_mlx_pixel_put(data, (int)p->x, (int)p->y, tmp);
		p->x += x_step;
		p->y += y_step;
	}
}

void	draw_map(t_map *map_data, t_point *p, t_point *p1, int x, int y, int q)
{
	shift_dot(&(*p), map_data);
	shift_dot(&(*p1), map_data);
	if (q)
		coloured_line(&(*p), &(*p1), map_data->img, map_data->colour, x, y);
	else
		draw_line(&(*p), &(*p1), map_data->img, map_data->colour);
}

void	side_lightning(t_map *map, int x, int y, char axis)
{
	if (axis == 'w')
	{
		if (y == 0 && x + 1 > 0)
			map->colour = 0x0000ff;
		else 
			map->colour = map->colours[y][x];
		if (y == map->height - 1 && x + 1 > 0)
			map->colour = 0x0000ff;	
	}
	else
	{
		if ((x == 0 && y + 1 > 0) || (x == map->width - 1 && y + 1 > 0))
			map->colour = 0x0000ff;
	}
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
			if (x < map_data->width - 1)
			{
				change_x1(map_data, x, y, &p1);
				side_lightning(map_data, x, y, 'w');
				draw_map(map_data, &p, &p1, x, y, 0);
			}
			if (y < map_data->height - 1)
			{
				map_data->colour = 0x00faff0; // 0xfbf00f0
				change_x_y(map_data, x, y, &p);
				change_y1(map_data, x, y, &p1);
				side_lightning(map_data, x, y, 'h');
				draw_map(map_data, &p, &p1, x, y, 0);
			}
		}
	}
}

void	isometric_map(t_map *map, t_data *data, int i)
{
	t_point	p;
	t_point	p1;
	int		w, q = 0;

	w = map->width;
	while (++i < map->height * w)
	{
		q = 0;
		change_x_y(map, i % w, i / w, &p);
		if (i % w < w - 1)
		{
			change_x1(map, i % w, i / w, &p1);
			side_lightning(map, i % w, i / w, 'w');
			isom(&p, (map->z_matrix[i / w][i % w] * map->zoom / 2));
			isom(&p1, (map->z_matrix[i / w][i % w + 1] * map->zoom / 2));
			if ((map->z_matrix[i / w][i % w] == 0 && map->z_matrix[i / w][i % w + 1] > 0)
				|| (map->z_matrix[i / w][i % w] > 0 && map->z_matrix[i / w][i % w + 1] == 0)
				|| (map->z_matrix[i / w][i % w] > 0 && map->z_matrix[i / w][i % w + 1] > 0))
				q = 1;
			draw_map(map, &p, &p1, i % w, i / w, q);
		}
		if (i / w < map->height - 1)
		{
			map->colour = map->colours[i / w][i % w];
			change_x_y(map, i % w, i / w, &p);
			change_y1(map, i % w, i / w, &p1);
			side_lightning(map, i % w, i / w, 'h');
			isom(&p, (map->z_matrix[i / w][i % w] * map->zoom / 2));
			isom(&p1, (map->z_matrix[i / w + 1][i % w] * map->zoom / 2));
			if ((map->z_matrix[i / w][i % w] == 0 && map->z_matrix[i / w + 1][i % w] > 0)
				|| (map->z_matrix[i / w][i % w] > 0 && map->z_matrix[i / w + 1][i % w] == 0)
				|| (map->z_matrix[i / w][i % w] > 0 && map->z_matrix[i / w][i % w] > 0))
				q = 1;
			draw_map(map, &p, &p1, i % w, i / w, q);
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
