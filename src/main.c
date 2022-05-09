/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 16:35:54 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int main(int argc, char **argv)
{
	t_data	d;
	// t_vars	vars;
	// t_shape	*shape;
	// t_light	*light;
	t_scene s;
//	t_vect	ray_dir;

	// d = malloc(sizeof(t_data));
	// init_scene(&s);
	if (argc == 2)
	{
		if (read_file(&s, argv[1]))
		{
			free_scene_el(&s);
			ft_error();
		}
		init_data(&d, &s);
		// d.mlx = mlx_init();
		// d.win = mlx_new_window(d.mlx, 1250, 1250, "miniRT");
		// d.img = mlx_new_image(d.mlx, 1250, 1250);
		// (void)argv;
		// shape = malloc(sizeof(t_shape));
		// light = malloc(sizeof(t_light));
		// if (shape == 0 || light == 0)
		// 	return (1);
		// if (parse_scene(shape, argv[1]))
		// 	ft_error();
		// d.s = &s;
		// d.h = 1250;
		// d.w = 1250;
		// printf("shape->type = %s\n", shape->type);
		// printf("shape->coordinates[0] = %f\n", shape->coordinates[0]);
		// printf("shape->coordinates[1] = %f\n", shape->coordinates[1]);
		// printf("shape->coordinates[2] = %f\n", shape->coordinates[2]);
		// printf("shape->diameter = %f\n", shape->diameter);
		// vars.shape = shape;
		// light->coordinates[0] = 15;
		// light->coordinates[1] = 40;
		// light->coordinates[2] = 0;
		// light->ratio = 0.7;

		// d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel,
		// 		&d.line_length, &d.endian);
//		if (ray_tracing(d, d.s->stack, d.s->light))
//		camera_dir(&ray_dir, d);
		if (ray_tracing(d))
			ft_error();
		mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
		mlx_hook(d.win, 2, 1L << 0, my_close, &d);
		mlx_hook(d.win, 17, 0, close_win, &d);
		mlx_loop(d.mlx);
	}
	else
		ft_error();
	return (0);
}
