/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/04/28 12:49:09 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int main(int argc, char **argv)
{
	t_data	data;
	// t_vars	vars;
	// t_shape	*shape;
	// t_light	*light;
	t_scene scene;

	double	test[4][4];
	double	**res;

	// data = malloc(sizeof(t_data));
	// init_scene(&scene);
	if (argc == 2)
	{
		if (read_file(&scene, argv[1]))
		{
			free_scene_el(&scene);
			ft_error();
		}
		init_data(&data, &scene);
		// data.mlx = mlx_init();
		// data.win = mlx_new_window(data.mlx, 1250, 1250, "miniRT");
		// data.img = mlx_new_image(data.mlx, 1250, 1250);
		// (void)argv;
		// shape = malloc(sizeof(t_shape));
		// light = malloc(sizeof(t_light));
		// if (shape == 0 || light == 0)
		// 	return (1);
		// if (parse_scene(shape, argv[1]))
		// 	ft_error();
		// data.scene = &scene;
		// data.height = 1250;
		// data.width = 1250;
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

		// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
		// 		&data.line_length, &data.endian);
//		if (ray_tracing(data, data.scene->stack, data.scene->light))
		if (ray_tracing(data))
			ft_error();
	
		test[0][0] = 3;
		test[0][1] = 2;
		test[0][2] = -1;
		test[0][3] = 1;
		test[1][0] = 1;
		test[1][1] = 0;
		test[1][2] = 1;
		test[1][3] = 2;
		test[2][0] = 2;
		test[2][1] = 1;
		test[2][2] = 1;
		test[2][3] = -1;
		test[3][0] = 1;
		test[3][1] = 1;
		test[3][2] = 1;
		test[3][3] = 0;

		res = matrix_inv(test, 4);
		printf("WOOHOO\n");
		int i = -1;
		int j;
		while (++i < 4)
		{
			j = -1;
			while (++j < 4)
			{
				if (j == 3)
					printf("%f\n", res[i][j]);
				else
					printf("%f ", res[i][j]);
			}

		}




		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L << 0, my_close, &data);
		mlx_hook(data.win, 17, 0, close_win, &data);
		mlx_loop(data.mlx);
	}
	else
		ft_error();
	return (0);
}
