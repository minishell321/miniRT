/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 07:53:15 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 10:06:54 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	sphere_intersection(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	coeff[3];
	float	t;
	float	delta;
	t_vect	d2shape;

//	d2shape = malloc(sizeof(double) * 3);
	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	coeff[0] = 1;
	coeff[1] = 2 * dot_product(&ray->dir, &d2shape);
	coeff[2] = norm_sq(&d2shape) - (shape->diameter * shape->diameter / 4);
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
//	free(d2shape);
	if (delta < 0 || (-coeff[1] + sqrt(delta)) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrt(delta)) / (2 * coeff[0]) > 0)
		t = (-coeff[1] - sqrt(delta)) / (2 * coeff[0]);
	else
	{
		t = (-coeff[1] + sqrt(delta)) / (2 * coeff[0]);
	}
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, nrm);
	nrm = normalize(nrm);
	return (t);
}

float	cyl_intersect_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
//	double	*u;
//	double	*v;
//	double	*d2shape;
	t_vect	u;
	t_vect	v;
	t_vect	d2shape;
	float	coeff[3];
	float	t;
	float	delta;

//	u = malloc(sizeof(double) * 3);
//	v = malloc(sizeof(double) * 3);
//	d2shape = malloc(sizeof(double) * 3);
	vec_cross_prod(&ray->dir, &shape->vect_3d, &u);
	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	vec_cross_prod(&d2shape, &shape->vect_3d, &v);
	coeff[0] = dot_product(&u, &u);
	coeff[1] = 2 * dot_product(&u, &v);
	coeff[2] = dot_product(&v, &v) - (shape->diameter * shape->diameter / 4);
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	if (delta < 0 || (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrtf(delta)) / (2 * coeff[0]) > 0)
		t = (-coeff[1] - sqrtf(delta)) / (2 * coeff[0]);
	else
	{
		t = (-coeff[1] + sqrtf(delta)) /  (2 * coeff[0]);
	}
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, &d2shape);
	vec_cross_prod(&shape->vect_3d, &d2shape, &u);
	vec_cross_prod(&u, &shape->vect_3d, nrm);
	nrm = normalize(nrm);
	vec_sub(pos, &shape->coordinates, &v);
	if (fabs(dot_product(&v, &shape->vect_3d)) < (shape->h / 2))
		return (t);
	return (0);
}

float	cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
//	double	*u;
//	double	*v;
//	double	*tmp;
	t_vect	u;
	t_vect	v;
	t_vect	tmp;
	float	denom;
	float	t[3];
	float	t_min;

//	u = malloc(sizeof(double) * 3);
//	v = malloc(sizeof(double) * 3);
//	tmp = malloc(sizeof(double) * 3);
	vec_scalar_multip(shape->h / 2, &shape->vect_3d, &tmp);
	vec_add(&tmp, &shape->coordinates, &u);
	vec_sub(&shape->coordinates, &tmp, &v);
	t[0] = cyl_intersect_open(ray, shape, pos, nrm);
	if (t[0])
		return (t[0]);
	vec_sub(&u, &ray->org, &tmp);
	denom = dot_product(&ray->dir, normalize(&shape->vect_3d));
	if (denom == 0)
		return (0);
	t[1] = dot_product(&tmp, normalize(&shape->vect_3d)) / denom;
	vec_sub(&v, &ray->org, &tmp);
	t[2] = dot_product(&tmp, normalize(&shape->vect_3d)) / denom;
	if (t[1] <= 0 || t[2] <= 0)
		return (0);
	if (t[1] < t[2])
		t_min = t[1];
	else
		t_min = t[2];
	
//	if (t[0] && t[0] < t_min)
//		return (t[0]);
	vec_scalar_multip(t_min, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->vect_3d.x, shape->vect_3d.y, shape->vect_3d.z);
	nrm = normalize(nrm);
	if (t[1] > t[2])
	{
		// vec_assign(nrm, v[0], v[1], v[2]);
		// nrm = normalize(nrm);
		vec_scalar_multip(-1, nrm, nrm);
	}
	vec_sub(pos, &u, &tmp);
	vec_sub(pos, &v, &u);
	if (dot_product(&tmp, &tmp) <= (shape->diameter * shape->diameter / 4)
			|| dot_product(&u, &u) <= (shape->diameter * shape->diameter / 4))
		return (t_min);

/*
	t = cyl_intersect_open(ray, shape, pos, nrm);
	vec_sub(pos, shape->coordinates, tmp);
	if (t)
		return (t);
	if (fabs(dot_product(tmp, shape->vect_3d)) == (shape->h / 2))
	{
		vec_sub(u, ray->org, tmp);
		delta = dot_product(tmp, normalize(shape->vect_3d));
		if (delta == 0)
			return (0);
		t = dot_product(ray->dir, normalize(shape->vect_3d));
		if (t <= 0)
			return (0);
		vec_assign(nrm, shape->vect_3d[0], shape->vect_3d[1], shape->vect_3d[2]);
		vec_sub(pos, u, tmp);
		if (dot_product(tmp, tmp) <= (shape->diameter * shape->diameter / 4))
			return (t);
	}
*/
	return (0);
}

float	plan_intersection(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	t;
	float	denom1;
	float	denom2;
	t_vect	tmp;

	vec_sub(&shape->coordinates, &ray->org, &tmp);
	denom1 = dot_product(&tmp, normalize(&shape->vect_3d));
	denom2 = dot_product(&ray->dir, normalize(&shape->vect_3d));
	if (denom2 == 0)
		return (0);
	t = denom1 / denom2;
	if (t <= 0)
		 return (0);
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->vect_3d.x, shape->vect_3d.y, shape->vect_3d.z);
	nrm = normalize(nrm);
	return (t);
}