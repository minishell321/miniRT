/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 07:53:15 by rburri            #+#    #+#             */
/*   Updated: 2022/05/12 17:54:24 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	sphere_intersection(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	coeff[3];
	float	t;
	float	delta;
	t_vect	d2shape;

	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	coeff[0] = 1;
	coeff[1] = 2 * dot_product(&ray->dir, &d2shape);
	coeff[2] = norm_sq(&d2shape) - (shape->diameter * shape->diameter / 4);
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	if (delta < 0 || (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]) < 0)
        return (0);
    if ((-coeff[1] - sqrtf(delta)) / (2 * coeff[0]) > 0)
        t = (-coeff[1] - sqrtf(delta)) / (2 * coeff[0]);
    else
		t = (-coeff[1] + sqrtf(delta)) /  (2 * coeff[0]);
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, nrm);
	nrm = normalize(nrm);
	return (t);
}

float	cyl_intersect_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_vect	u;
	t_vect	v;
	t_vect	d2shape;
	float	coeff[3];
	float	t_d[2];

	vec_cross_prod(&ray->dir, &shape->vect_3d, &u);
	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	vec_cross_prod(&d2shape, &shape->vect_3d, &v);
	coeff[0] = dot_product(&u, &u);
	coeff[1] = 2 * dot_product(&u, &v);
	coeff[2] = dot_product(&v, &v) - (shape->diameter * shape->diameter / 4);
	t_d[1] = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	if (t_d[1] < 0 || (-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrtf(t_d[1])) / (2 * coeff[0]) > 0)
		t_d[0] = (-coeff[1] - sqrtf(t_d[1])) / (2 * coeff[0]);
	else
		t_d[0] = (-coeff[1] + sqrtf(t_d[1])) /  (2 * coeff[0]);
	vec_scalar_multip(t_d[0], &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, &d2shape);
	vec_cross_prod(&shape->vect_3d, &d2shape, &u);
	vec_cross_prod(&u, &shape->vect_3d, nrm);
	nrm = normalize(nrm);
	vec_sub(pos, &shape->coordinates, &v);
	if (fabs(dot_product(&v, &shape->vect_3d)) < (shape->h / 2))
		return (t_d[0]);
	return (0);
}

float	cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_vect	u;
	t_vect	v;
	t_vect	tmp;
	float	d_t_min[2];
	float	t[3];

	vec_scalar_multip(shape->h / 2, normalize(&shape->vect_3d), &tmp);
	vec_add(&tmp, &shape->coordinates, &u);
	vec_sub(&shape->coordinates, &tmp, &v);
	vec_sub(&u, &ray->org, &tmp);
	d_t_min[0] = dot_product(&ray->dir, &shape->vect_3d);
	if (d_t_min[0] == 0)
		return (cyl_intersect_open(ray,shape,pos,nrm));
	t[1] = dot_product(&tmp, normalize(&shape->vect_3d)) / d_t_min[0];
	vec_sub(&v, &ray->org, &tmp);
	t[2] = dot_product(&tmp, normalize(&shape->vect_3d)) / d_t_min[0];
	if (t[1] <= 0 || t[2] <= 0)
		return (cyl_intersect_open(ray,shape,pos,nrm));	
	if (t[1] < t[2])
		d_t_min[1] = t[1];
	else
		d_t_min[1] = t[2];
	vec_scalar_multip(d_t_min[1], &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->vect_3d.x, shape->vect_3d.y, shape->vect_3d.z);
	nrm = normalize(nrm);
	if (t[1] > t[2])
		vec_scalar_multip(-1, nrm, nrm);
	vec_sub(pos, &u, &tmp);
	vec_sub(pos, &v, &u);
	if (dot_product(&tmp, &tmp) <= (shape->diameter * shape->diameter / 4)
			|| dot_product(&u, &u) <= (shape->diameter * shape->diameter / 4))
		return (d_t_min[1]);
	else
		return (cyl_intersect_open(ray, shape, pos, nrm));
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
