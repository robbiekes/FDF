/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:21:39 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/25 15:23:30 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_y1(t_map *map_data, int x, int y, t_point *p1)
{
	p1->x = x * map_data->zoom;
	p1->y = (y + 1) * map_data->zoom;
}

void	change_x1(t_map *map_data, int x, int y, t_point *p1)
{
	p1->x = (x + 1) * map_data->zoom;
	p1->y = y * map_data->zoom;
}

void	change_x_y(t_map *map_data, int x, int y, t_point *p)
{
	p->x = x * map_data->zoom;
	p->y = y * map_data->zoom;
}

void	shift_dot(t_point *p, t_map *map_data)
{
	p->x += map_data->shift_x;
	p->y += map_data->shift_y;
}

void	isom(t_point *p, int z)
{
	p->x = (p->x - p->y) * cos(0.8);
	p->y = (p->x + p->y) * sin(0.8) - z;
}
