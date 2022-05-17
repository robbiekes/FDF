/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:19:35 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/25 15:42:12 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_arrays(t_map *map_data, int **arr)
{
	int	i;

	i = 0;
	while (i < map_data->height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_splitted_exit(char **arr, int flag)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
	if (flag)
		finish(0);
}

int	ft_ptrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
	return (i);
}

void	finish(int exitcode)
{
	if (exitcode)
		write(1, "Error\n", 6);
	exit(exitcode);
}

int	ft_atoi(char *str)
{
	int			sign;
	long int	num;
	int			i;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	return (num * sign);
}
