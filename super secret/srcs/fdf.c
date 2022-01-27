/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:38:12 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/25 15:44:31 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->address + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	update_img(t_map *map_data, int key)
{
	static int	view_mode = 0;

	background(map_data);
	if (key == 19)
		view_mode = 1;
	if (key == 20)
		view_mode = 0;
	if (view_mode)
		view_above(map_data, map_data->img, -1, -1);
	else
		isometric_map(map_data, map_data->img, -1);
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr,
		map_data->img->image, 0, 0);
}

int	key_num(int key, t_map *map_data)
{
	if (key == 124)
		map_data->shift_x += 5;
	else if (key == 123)
		map_data->shift_x -= 5;
	else if (key == 126)
		map_data->shift_y -= 5;
	else if (key == 125)
		map_data->shift_y += 5;
	else if (key == 53)
		exit (0);
	else if (key == 13)
		map_data->zoom += map_data->zoom / 25;
	else if (key == 1)
		map_data->zoom -= map_data->zoom / 25;
	else if (key == 19)
		view_above(map_data, map_data->img, -1, -1);
	else if (key == 20)
		isometric_map(map_data, map_data->img, -1);
	else
		return (0);
	update_img(map_data, key);
	return (0);
}

int	mouse_zoom(int key, int x, int y, t_map *map_data)
{
	float	zoom;

	zoom = map_data->zoom;
	if (key == MOUSE_UP && zoom < 100)
		map_data->zoom += zoom / 16;
	else if (key == MOUSE_DOWN && zoom > 1.1)
		map_data->zoom -= zoom / 16;
	else if (key == 19)
		view_above(map_data, map_data->img, -1, -1);
	else
		isometric_map(map_data, map_data->img, -1);
	update_img(map_data, key);
	return (x + y);
}

void	fdf(char **argv)
{
	t_data	img;
	t_map	*map_data;

	map_data = (t_map *)malloc(sizeof(t_map));
	read_map(argv[1], map_data);
	map_data->mlx_ptr = mlx_init();
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr, HEIGHT, WIDTH, "FDF");
	img.image = mlx_new_image(map_data->mlx_ptr, HEIGHT, WIDTH);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	map_data->zoom = 20;
	map_data->img = &img;
	map_data->shift_x = 300;
	map_data->shift_y = 200;
	isometric_map(map_data, map_data->img, -1);
	mlx_hook(map_data->win_ptr, 4, 0, mouse_zoom, map_data);
	mlx_key_hook(map_data->win_ptr, key_num, map_data);
	mlx_put_image_to_window(map_data->mlx_ptr,
		map_data->win_ptr, img.image, 0, 0);
	mlx_loop(map_data->mlx_ptr);
	free_arrays(map_data, map_data->z_matrix);
	free_arrays(map_data, map_data->colours);
	free(map_data);
}
