/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:55:21 by rburri            #+#    #+#             */
/*   Updated: 2022/05/10 12:01:35 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

int	my_close(int keycode, t_data *d)
{
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->win);
		free_scene_el(d->s);
		exit(0);
	}
	return (0);
}

int	close_win(t_data *d)
{
	mlx_destroy_window(d->mlx, d->win);
	free_scene_el(d->s);
	exit (0);
}

unsigned int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_data(t_data *d, t_scene *s)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "miniRT");
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->s = s;
	d->h = HEIGHT;
	d->w = WIDTH;
	d->addr = mlx_get_data_addr(d->img, &d->bits_per_pixel,
			&d->line_length, &d->endian);
}
