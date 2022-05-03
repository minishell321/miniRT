/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/03 12:05:58 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersection(t_ray *ray, t_shapes *shape, double *pos, double *nrm)
{
	double	coeff[3];
	double	t;
	double	delta;
	double	*d2shape;

	d2shape = malloc(sizeof(double) * 3);
	vec_sub(ray->org, shape->coordinates, d2shape);
	coeff[0] = 1;
	coeff[1] = 2 * dot_product(ray->dir, d2shape);
	coeff[2] = norm_squared(d2shape) - (shape->diameter * shape->diameter / 4);
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	free(d2shape);
	if (delta < 0 || (-coeff[1] + sqrt(delta)) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrt(delta)) / (2 * coeff[0]) > 0)
		t = (-coeff[1] - sqrt(delta)) / (2 * coeff[0]);
	else
	{
		t = (-coeff[1] + sqrt(delta)) / (2 * coeff[0]);
	}
	vec_scalar_multip(t, ray->dir, pos);
	vec_add(ray->org, pos, pos);
	vec_sub(pos, shape->coordinates, nrm);
	nrm = normalize(nrm);
	return (t);
}

double	plan_intersection(t_ray *ray, t_shapes *shape, double *pos, double *nrm)
{
	double	t;
	double	denom1;
	double	denom2;
	double	*tmp;

	tmp = malloc(sizeof(double) * 3);
	vec_sub(shape->coordinates, ray->org, tmp);

//	denom1 = dot_product(vec_sub(pos, shape->coordinates, nrm), shape->coordinates);
	
	denom1 = dot_product(tmp, normalize(shape->vect_3d));
	denom2 = dot_product(ray->dir, normalize(shape->vect_3d));
	if (denom2 == 0)
		return (0);
	t = denom1 / denom2;
	if (t <= 0)
		 return (0);
	vec_scalar_multip(t, ray->dir, pos);
    vec_add(ray->org, pos, pos);
    // vec_sub(pos, shape->coordinates, nrm);
	nrm[0] = shape->vect_3d[0];
	nrm[1] = shape->vect_3d[1];
	nrm[2] = shape->vect_3d[2];
    nrm = normalize(nrm);
	return (t);
}

double	*dir_vec(double *ray_dir, int i, int j, t_data data)
{
	ray_dir[0] = j - data.width / 2;
	ray_dir[1] = i - data.height / 2;
	ray_dir[2] = -data.width / (2 * tan (data.scene->camera->fov / 2));
	return (ray_dir);
}

int	scene_intersect(t_data data, t_ray *ray)
{
	int			has_intersect;
	t_shapes	*tmp;
	double		*position_tmp;
	double		*normal_tmp;
	double		ret;

	position_tmp = malloc(sizeof(double) * 3);
	normal_tmp = malloc(sizeof(double) * 3);
	ray->intersect = 2147483647;
	has_intersect = 0;
	tmp = data.scene->stack;
	while (tmp)
	{
		// ret = plan_intersection(ray, tmp, position_tmp, normal_tmp);
		// if (ret && ret < ray->intersect)
		// {
		// 	has_intersect = 1;
		// 	ray->intersect = ret;
		// 	vec_dup(position_tmp, ray->pos);
		// 	vec_dup(normal_tmp, ray->nrm);
		// 	ray->sf_color[0] = tmp->colors[0];
		// 	ray->sf_color[1] = tmp->colors[1];
		// 	ray->sf_color[2] = tmp->colors[2];
		// }
		// tmp = tmp->next;
		if (tmp->type == SP)
		{
			ret = intersection(ray, tmp, position_tmp, normal_tmp);
			if (ret && ret < ray->intersect)
			{
				has_intersect = 1;
				ray->intersect = ret;
				vec_dup(position_tmp, ray->pos);
				vec_dup(normal_tmp, ray->nrm);
				ray->sf_color[0] = tmp->colors[0];
				ray->sf_color[1] = tmp->colors[1];
				ray->sf_color[2] = tmp->colors[2];
			}
		}
		else if (tmp->type == PL)
		{
			ret = plan_intersection(ray, tmp, position_tmp, normal_tmp);
			if (ret && ret < ray->intersect)
			{
				has_intersect = 1;
				ray->intersect = ret;
				vec_dup(position_tmp, ray->pos);
				vec_dup(normal_tmp, ray->nrm);
				ray->sf_color[0] = tmp->colors[0];
				ray->sf_color[1] = tmp->colors[1];
				ray->sf_color[2] = tmp->colors[2];
			}
		}
		tmp = tmp->next;
	}
	free(position_tmp);
	free(normal_tmp);
	return (has_intersect);
}

int	ray_tracing(t_data data)
{
	int		i;
	int		j;
	t_ray	*ray;
	t_ray	*light;

	i = 0;
	ray = malloc(sizeof(t_ray));
	light = malloc(sizeof(t_ray));
	if (ray == 0 || init_ray(ray) || light == 0 || init_ray(light))
		return (1);
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
		{
			ray->dir = normalize(dir_vec(ray->dir, i, j, data));
			vec_dup(data.scene->camera->coordinates, ray->org);
			if (scene_intersect(data, ray))
			{
				vec_add(ray->pos, light->org, light->org);
				vec_sub(data.scene->light->coordinates, ray->pos, ray->pos);
				vec_scalar_multip(0.01, ray->nrm, light->org);
				vec_dup(ray->pos, light->dir);
				light->dir = normalize(light->dir);
				if (!(scene_intersect(data, light) && (light->intersect * light->intersect < norm_squared(ray->pos))))
				{
					pixel_colors(data, ray);
					my_mlx_pixel_put(&data, j, data.height - i - 1, data.scene->stack->color);
				}
			}
			j++;
		}
		i++;
	}
	free_ray(ray);
	free_ray(light);
	return (0);
}
