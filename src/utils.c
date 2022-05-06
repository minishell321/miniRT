/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:55:21 by rburri            #+#    #+#             */
/*   Updated: 2022/05/06 13:06:54 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

int	my_close(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		free_scene_el(data->scene);
		exit(0);
	}
	return (0);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_scene_el(data->scene);
	exit (0);
}

unsigned int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_data(t_data *data, t_scene *scene)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->scene = scene;
	data->height = HEIGHT;
	data->width = WIDTH;
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}
