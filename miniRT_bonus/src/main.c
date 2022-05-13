/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/05/11 07:55:32 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_data	d;
	t_scene	s;

	if (argc == 2)
	{
		init_data(&d, &s);
		if (read_file(&s, argv[1]))
			free_scene_el(&s);
		check_scene_compete(&d);
		if (ray_tracing(d))
			ft_err("ray_tracing");
		mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
		mlx_hook(d.win, 2, 1L << 0, my_close, &d);
		mlx_hook(d.win, 17, 0, close_win, &d);
		mlx_loop(d.mlx);
	}
	else
		ft_err("Bad Arguments");
	return (0);
}
