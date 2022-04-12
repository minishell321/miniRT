/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/04/12 16:58:08 by vbotev           ###   ########.fr       */
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
//int	intersection(double *ray_dir, double *sphere, double sp_diameter, double *position, double *normal)
double	intersection(double *ray_origin, double *ray_dir, double *sphere, double sp_diameter, double *position, double *normal)
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	delta;
	double	dist_to_sphere_center[3];

	dist_to_sphere_center[0] = ray_origin[0] - sphere[0];
	dist_to_sphere_center[1] = ray_origin[1] - sphere[1];
	dist_to_sphere_center[2] = ray_origin[2] - sphere[2];
	a = 1;
	b = 2 * dot_product(ray_dir, dist_to_sphere_center);
	c = norm_squared(dist_to_sphere_center) - (sp_diameter / 2 * sp_diameter / 2);
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
	return (t);
//	return (1);
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

int	scene_intersect(double *ray_origin, double *ray_dir, t_data data, double *position, double *normal)
{
	int			has_intersect;
	t_shapes	*tmp;
	double		solution_min;
	double		*position_tmp;
	double		*normal_tmp;
	double		ret;

	position_tmp = malloc(sizeof(double) * 3);
	normal_tmp = malloc(sizeof(double) * 3);
	solution_min = 2147483647;
	has_intersect = 0;
	tmp = data.scene->stack;
	while(tmp)
	{
		ret = intersection(ray_origin, ray_dir, tmp->coordinates, tmp->diameter, position_tmp, normal_tmp);
		if (ret && ret < solution_min)
		{
		//	has_intersect = 1;
			solution_min = ret;
			has_intersect = solution_min;
			position[0] = position_tmp[0];
			position[1] = position_tmp[1];
			position[2] = position_tmp[2];
			normal[0] = normal_tmp[0];
			normal[1] = normal_tmp[1];
			normal[2] = normal_tmp[2];
		}
		tmp = tmp->next;
	}
	free(position_tmp);
	free(normal_tmp);
	return (has_intersect);
}

// FOV SET TO 60 degrees
//int	ray_tracing(t_data data, t_shapes *shape, t_light *light)
int	ray_tracing(t_data data, t_light *light)
{
	int		i;
	int		j;
	double	fov;
	double	t_light;
	double	*ray_dir;
	double	*ray_light;
	double	*position;
	double	*pos_light;
	double	*normal;
	double	*nrm_light;
	double	*tmp;
	double	pixel_intensity;

	i = 0;
	fov = 60 * M_PI / 180;
	ray_dir = malloc(sizeof(double) * 3);
	position = malloc(sizeof(double) * 3);
	pos_light = malloc(sizeof(double) * 3);
	normal = malloc(sizeof(double) * 3);
	nrm_light = malloc(sizeof(double) * 3);
	ray_light = malloc(sizeof(double) * 3);
	tmp = malloc(sizeof(double) * 3);
	if (ray_dir == 0 || position == 0 || pos_light == 0 || normal == 0 || nrm_light == 0 || ray_light == 0 || tmp == 0)
		return (1);
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
		{
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
//			if (intersection(normalize(dir_vec(ray_dir, i, j, data.width, data.height, fov)), shape->coordinates, shape->diameter, position, normal))
			if (scene_intersect(tmp, normalize(dir_vec(ray_dir, i, j, data.width, data.height, fov)), data, position, normal))
			{
				tmp[0] = position[0] + 0.0001 * normal[0];
				tmp[1] = position[1] + 0.0001 * normal[1];
				tmp[2] = position[2] + 0.0001 * normal[2];
				position[0] = light->coordinates[0] - position[0];
				position[1] = light->coordinates[1] - position[1];
				position[2] = light->coordinates[2] - position[2];
				ray_light[0] = position[0];
				ray_light[1] = position[1];
				ray_light[2] = position[2];
				ray_light = normalize(ray_light);
				t_light = scene_intersect(tmp, ray_light, data, pos_light, nrm_light);
				if (!(t_light && (t_light * t_light < norm_squared(position))))
				{
				tmp[0] = position[0];
				tmp[1] = position[1];
				tmp[2] = position[2];
				tmp = normalize(tmp);
				ray_light[0] = tmp[0];
				ray_light[1] = tmp[1];
				ray_light[2] = tmp[2];
				
				pixel_intensity = light->ratio * 1000000 * fmax(0, dot_product(tmp, normal)) / (norm_squared(position));
				my_mlx_pixel_put(&data, j, data.height - i - 1, (dec2hex(fmin(255, fmax(0, pixel_intensity)))));
				}
			}
			j++;
		}
		i++;
	}
	free(ray_dir);
	free(position);
	free(pos_light);
	free(normal);
	free(nrm_light);
	free(ray_light);
	free(tmp);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	// t_vars	vars;
	// t_shape	*shape;
	// t_light	*light;
	t_scene scene;

	// data = malloc(sizeof(t_data));
	// init_scene(&scene);
	if (argc == 2)
	{
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, 1250, 1250, "miniRT");
		data.img = mlx_new_image(data.mlx, 1250, 1250);
		// (void)argv;
		// shape = malloc(sizeof(t_shape));
		// light = malloc(sizeof(t_light));
		// if (shape == 0 || light == 0)
		// 	return (1);
		// if (parse_scene(shape, argv[1]))
		// 	ft_error();
		if (read_file(&scene, argv[1]))
			ft_error();
		data.scene = &scene;
		data.height = 1250;
		data.width = 1250;
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

		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
				&data.line_length, &data.endian);
//		if (ray_tracing(data, data.scene->stack, data.scene->light))
		if (ray_tracing(data, data.scene->light))
			ft_error();
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L << 0, my_close, &data);
		mlx_loop(data.mlx);
	}
	else
		ft_error();
	return (0);
}
