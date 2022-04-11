/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 17:56:01 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double norm_squared(double *crdnt)
{
	double	res;

	res = crdnt[0] * crdnt[0] + crdnt[1] * crdnt[1] + crdnt[2] * crdnt[2];
	return(res);
}

double	*normalize(double *crdnt)
{
	double	norm;

	norm = sqrt(norm_squared(crdnt));
	crdnt[0] = crdnt[0] / norm;
	crdnt[1] = crdnt[1] / norm;
	crdnt[2] = crdnt[2] / norm;
	return (crdnt);
}

double	dot_product(double *a, double *b)
{
	double	result;

	result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return (result);
}

// ASSUMING AN ORIGIN OF THE RAY AT {0, 0, 0}
int	intersection(double *ray_dir, double *sphere, double sp_diameter, double *position, double *normal)
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	delta;
	double	dist_to_sphere_center[3];

	// using {0,0,0} as origin otherwise this would have to be modified
	dist_to_sphere_center[0] = -1 * sphere[0];
	dist_to_sphere_center[1] = -1 * sphere[1];
	dist_to_sphere_center[2] = -1 * sphere[2];
	a = 1;
	b = 2 * dot_product(ray_dir, dist_to_sphere_center);
	c = norm_squared(dist_to_sphere_center) - (sp_diameter * sp_diameter);
	delta = b * b - (4 * a * c);
	if (delta < 0)
		return (0);
	if ((-b + sqrt(delta)) / (2 * a) < 0)
		return (0);
	if ((-b - sqrt(delta)) / (2 * a) > 0)
		t = (-b -sqrt(delta)) / (2 * a);
	else
	{	
		t = (-b + sqrt(delta)) / (2 * a);
	}
	position[0] = t * ray_dir[0];
	position[1] = t * ray_dir[1];
	position[2] = t * ray_dir[2];
	normal[0] = position[0] - sphere[0];
	normal[1] = position[1] - sphere[1];
	normal[2] = position[2] - sphere[2];
	normal = normalize(normal);	
	return (1);
}

unsigned int	dec2hex(int n)
{
	unsigned int	hex;

	hex = 0;

	//hex = pow(16, 7) * (n / 16);
	//hex = pow(16, 6) * (n % 16);
	hex += pow(16, 5) * (n / 16);
	hex += pow(16, 4) * (n % 16);
	hex += pow(16, 3) * (n / 16);
	hex += pow(16, 2) * (n % 16);
	hex += pow(16, 1) * (n / 16);
	hex += n % 16;
	return (hex);
}

double *dir_vec(double *ray_dir, int i, int j, int W, int H, double fov)
{
	ray_dir[0] = j - W / 2;
	ray_dir[1] = i - H / 2;
	ray_dir[2] = -W / (2 * tan (fov / 2));
	return (ray_dir);
}

// FOV SET TO 60 degrees
int	ray_tracing(t_data img, t_shape *shape, t_light *light)
{
	int		i;
	int		j;
	double	fov;
	double	*ray_dir;
	double	*position;
	double	*normal;
	double	*tmp;
	double	pixel_intensity;

	i = 0;
	fov = 60 * M_PI / 180;
	ray_dir = malloc(sizeof(double) * 3);
	position = malloc(sizeof(double) * 3);
	normal = malloc(sizeof(double) * 3);
	tmp = malloc(sizeof(double) * 3);
	if (ray_dir == 0 || position == 0 || normal == 0 || tmp == 0)
		return (1);
	while (i < img.height)
	{
		j = 0;
		while (j < img.width)
		{
			if (intersection(normalize(dir_vec(ray_dir, i, j, img.width, img.height, fov)), shape->coordinates, shape->diameter, position, normal))
			{
				position[0] = light->coordinates[0] - position[0];
				position[1] = light->coordinates[1] - position[1];
				position[2] = light->coordinates[2] - position[2];
				tmp[0] = position[0];
				tmp[1] = position[1];
				tmp[2] = position[2];
				tmp = normalize(tmp);
				pixel_intensity = light->ratio * 1000000 * fmax(0, dot_product(tmp, normal)) / (norm_squared(position));
				my_mlx_pixel_put(&img, j, img.height - i - 1, (dec2hex(fmin(255, fmax(0, pixel_intensity)))));
			}
			j++;
		}
		i++;
	}
	free(ray_dir);
	free(position);
	free(normal);
	free(tmp);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	img;
	t_vars	vars;
	t_shape	*shape;
	t_light	*light;
	// t_scene *scene;

	if (argc == 2)
	{
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 1024, 1024, "miniRT");
		img.img = mlx_new_image(vars.mlx, 1024, 1024);
		(void)argv;
		shape = malloc(sizeof(t_shape));
		light = malloc(sizeof(t_light));
		if (shape == 0 || light == 0)
			return (1);
		if (parse_scene(shape, argv[1]))
			ft_error();
		img.height = 1024;
		img.width = 1024;
		printf("shape->type = %s\n", shape->type);
		printf("shape->coordinates[0] = %f\n", shape->coordinates[0]);
		printf("shape->coordinates[1] = %f\n", shape->coordinates[1]);
		printf("shape->coordinates[2] = %f\n", shape->coordinates[2]);
		printf("shape->diameter = %f\n", shape->diameter);
		vars.shape = shape;
		light->coordinates[0] = 15;
		light->coordinates[1] = 40;
		light->coordinates[2] = 0;
		light->ratio = 0.7;

		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		if (ray_tracing(img, shape, light))
			ft_error();
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_hook(vars.win, 2, 1L << 0, my_close, &vars);
		mlx_loop(vars.mlx);
	}
	else
		ft_error();
	return (0);
}
