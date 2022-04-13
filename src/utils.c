/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:55:21 by rburri            #+#    #+#             */
/*   Updated: 2022/04/13 10:59:31 by rburri           ###   ########.fr       */
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
		printf("before\n");
		mlx_destroy_window(data->mlx, data->win);
		printf("after\n");
		free_scene_el(data->scene);
		exit(0);
	}
	return (0);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
}

unsigned int	encode_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}
