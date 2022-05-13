/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 07:53:15 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 14:01:20 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	sphere_inter(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	coeff[3];
	float	t;
	float	delta;
	t_vect	d2shape;

	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	coeff[0] = 1;
	coeff[1] = 2 * dot_p(&ray->dir, &d2shape);
	coeff[2] = norm_sq(&d2shape) - (shape->diam * shape->diam / 4);
	delta = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	if (delta < 0 || (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrtf(delta)) / (2 * coeff[0]) > 0)
		t = (-coeff[1] - sqrtf(delta)) / (2 * coeff[0]);
	else
		t = (-coeff[1] + sqrtf(delta)) / (2 * coeff[0]);
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, nrm);
	nrm = normalize(nrm);
	return (t);
}

float	plan_inter(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	t;
	float	denom1;
	float	denom2;
	t_vect	tmp;

	vec_sub(&shape->coordinates, &ray->org, &tmp);
	denom1 = dot_p(&tmp, normalize(&shape->v_3d));
	denom2 = dot_p(&ray->dir, normalize(&shape->v_3d));
	if (denom2 == 0)
		return (0);
	t = denom1 / denom2;
	if (t <= 0)
		return (0);
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->v_3d.x, shape->v_3d.y, shape->v_3d.z);
	nrm = normalize(nrm);
	return (t);
}
