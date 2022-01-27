/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:30:04 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/25 15:43:35 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define MOUSE_DOWN	4
# define MOUSE_UP	5
# define HEIGHT		1000
# define WIDTH		1000

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_data
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_map
{
	int			height;
	int			width;
	float		zoom;
	int			colour;
	int			**z_matrix;
	int			**colours;
	int			shift_x;
	int			shift_y;
	void		*mlx_ptr;
	void		*win_ptr;

	t_data		*img;

}				t_map;

int		ft_max(int a, int b);
int		ft_abs(int a);
int		ft_atoi(char *str);
int		ft_atoi_base(char *str, char *base);
char	**ft_split(char *s, char c);
int		ft_ptrlen(char **s);

void	fdf(char **argv);
void	read_map(char *map, t_map *map_data);
void	fill_colours(t_map *map_data, char **str, int i);
void	fill_matrix(t_map *map_data, char *file);
void	background(t_map *map_data);
int		get_height(char *file);
int		get_width(char *file);
void	free_splitted_exit(char **arr, int flag);
char	*get_next_line(int fd);
void	finish(int exitcode);

void	draw_line(t_point *p, t_point *p1, t_data *data, int colour);
void	draw_map(t_map *map_data, t_point *p, t_point *p1);
void	view_above(t_map *map_data, t_data *data, int x, int y);
void	isometric_map(t_map *map, t_data *data, int i);
int		mouse_zoom(int key, int x, int y, t_map *map_data);
int		key_num(int key, t_map *map_data);
void	free_arrays(t_map *map_data, int **arr);
void	change_y1(t_map *map_data, int x, int y, t_point *p1);
void	change_x1(t_map *map_data, int x, int y, t_point *p1);
void	change_x_y(t_map *map_data, int x, int y, t_point *p);
void	shift_dot(t_point *p, t_map *map_data);
void	isom(t_point *p, int z);

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour);
void	update_img(t_map *map_data, int key);

#endif
