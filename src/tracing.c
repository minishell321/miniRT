/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/02 17:36:29 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	cyl_intersect(t_ray *ray, t_shapes *shape, double *pos, double *nrm)
{
	t_geo_tfrm	*tfrm;
	double		*trans;
	double		*rot;
	double		*scale;
	double		*tmp;
	double		coeff[3];
	double		delta;
	double		minValue;
	double		*t;
	int			i;
	int			minIndex;
	t_ray		*r_local;

	(void)shape;
	trans = malloc(sizeof(double) * 3);
	rot = malloc(sizeof(double) * 3);
	scale = malloc(sizeof(double) * 3);
	tmp = malloc(sizeof(double) * 3);
	vec_assign(trans, 0, 0, 0);
	vec_assign(rot, 0.6*M_PI, 0, 0);
	vec_assign(scale, 1.0, 1.0, 1.0);
	tfrm = NULL;
	tfrm = geo_transform(trans, rot, scale, tfrm);
	r_local = malloc(sizeof(t_ray));
	init_ray(r_local);
	vec_dup(ray->org, r_local->org);
	vec_dup(ray->dir, r_local->dir);
	vec_mat_multip(tfrm->bck, r_local->org, tmp);
	vec_dup(tmp, r_local->org);
	vec_mat_multip(tfrm->bck, r_local->dir, tmp);
	vec_dup(tmp, r_local->dir);
//	r_local->dir = normalize(r_local->dir);
	coeff[0] = pow(r_local->dir[0], 2) + pow(r_local->dir[1], 2);
	coeff[1] = 2 * (r_local->org[0] * r_local->dir[0] + r_local->org[1] * r_local->dir[1]);
	coeff[2] = pow(r_local->org[0], 2) + pow(r_local->org[1], 2) - 1;
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
//	poi = malloc(sizeof(double) * 4);
	t = malloc(sizeof(double) * 4);
	if (delta > 0)
	{
		t[0] = (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]);
		t[1] = (-coeff[1] - sqrtf(delta)) / (2 * coeff[0]);
		if (!(t[0] > 0 && (fabs(r_local->org[2] + r_local->dir[2] * t[0]) < 1)))
			t[0] = 100000000;
		//	return (t[0]);
	//	else
	//	{
//			t[0] = 100000000;
		//	return (0);
	//	}
		if (!(t[1] > 0 && (fabs(r_local->org[2] + r_local->dir[2] * t[1]) < 1)))
			t[1] = 100000000;
		//	return (t[1]);
	//	else
	//	{
	//		t[1] = 100000000;
		//	return (0);
	//	}
	}
	else
	{
		t[0] = 100000000;
		t[1] = 100000000;
	//	return (0);
	}
	if (r_local->dir[2] < 0.001)
	{
		t[2] = 100000000;
		t[3] = 100000000;
	//	return (0);
	}
	else
	{
		t[2] = (r_local->org[2] - 1) / (-r_local->dir[2]);
		t[3] = (r_local->org[2] + 1) / (-r_local->dir[2]);
		if (!(t[2] > 0 && sqrtf(pow(r_local->org[0] + r_local->dir[0] * t[2], 2) + pow(r_local->org[1] + r_local->dir[1] * t[2], 2)) < 1))
			t[2] = 100000000;
		//	return (t[2]);
	//	else
//			t[2] = 100000000;
		if (!(t[3] > 0 && sqrtf(pow(r_local->org[0] + r_local->dir[0] * t[3], 2) + pow(r_local->org[1] + r_local->dir[1] * t[3], 2)) < 1))
			t[3] = 100000000;
		//	return (t[3]);
	//	else
	//		t[3] = 100000000;
	}
	if (t[0] > 10000000 && t[1] > 10000000 && t[2] > 10000000 && t[3] > 10000000)
		return (0);
	i = -1;
	minIndex = 0;
	minValue = 10000000;
	while(++i < 4)
	{
		if (t[i] < minValue)
		{
			minValue = t[i];
			minIndex = i;
		}
	}
	if (minIndex < 2)
	{
		vec_scalar_multip(t[minIndex], r_local->dir, pos);
		vec_add(r_local->org, pos, pos);
		vec_mat_multip(tfrm->fwd, pos, tmp);
		vec_dup(tmp, pos);
		vec_assign(trans, 0, 0, 0);
		vec_mat_multip(tfrm->fwd, trans, tmp);
		vec_assign(nrm, pos[0], pos[1], 0);
		vec_mat_multip(tfrm->fwd, nrm, trans);
		vec_sub(trans, tmp, nrm);
		nrm = normalize(nrm);
		return (t[minIndex]);
	}
	else
	{
		if (r_local->dir[2] > 0.001)
		{
			if (sqrtf(pow(r_local->org[0] + r_local->dir[0] * t[minIndex], 2) + pow(r_local->org[1] + r_local->dir[1] * t[minIndex], 2)) < 1)
			{
				vec_scalar_multip(t[minIndex], r_local->dir, pos);
				vec_add(r_local->org, pos, pos);
				vec_mat_multip(tfrm->fwd, pos, tmp);
				vec_dup(tmp, pos);
				vec_assign(trans, 0, 0, 0);
				vec_mat_multip(tfrm->fwd, trans, tmp);
				vec_assign(nrm, 0, 0, (0 + r_local->org[2] + r_local->dir[2] * t[minIndex]));
				vec_mat_multip(tfrm->fwd, nrm, trans);
				vec_sub(trans, tmp, nrm);
				nrm = normalize(nrm);
				return (t[minIndex]);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (0);
}

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
	if (delta < 0 || (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrtf(delta)) / (2 * coeff[0]) > 0)
		t = (-coeff[1] - sqrtf(delta)) / (2 * coeff[0]);
	else
	{
		t = (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]);
	}
	vec_scalar_multip(t, ray->dir, pos);
	vec_add(ray->org, pos, pos);
	vec_sub(pos, shape->coordinates, nrm);
	nrm = normalize(nrm);
	return (t);
}

double	*dir_vec(double *ray_dir, int i, int j, t_data data)
{
	ray_dir[0] = j - data.width / 2;
	ray_dir[1] = i - data.height / 2;
//	ray_dir[2] = -data.width / (2 * tan (data.scene->camera->fov / 2));
	ray_dir[2] = data.scene->camera->coordinates[2] - data.width / (2 * tan (data.scene->camera->fov / 2));
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
	//	ret = intersection(ray, tmp, position_tmp, normal_tmp);
		ret = cyl_intersect(ray, tmp, position_tmp, normal_tmp);
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
				vec_scalar_multip(0.000001, ray->nrm, light->org);
				vec_add(ray->pos, light->org, light->org);
				vec_sub(data.scene->light->coordinates, ray->pos, ray->pos);
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
