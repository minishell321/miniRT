/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter_cy_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:18 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 12:31:40 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static float	t_d_calc(float coeff[3], t_shapes *shape, t_vect *u, t_vect *v)
{
	coeff[0] = dot_p(u, u);
	coeff[1] = 2 * dot_p(u, v);
	coeff[2] = dot_p(v, v) - (shape->diam * shape->diam / 4);
	return (coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]));
}

float	cyl_inter_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_vect	u;
	t_vect	v;
	t_vect	d2shape;
	float	coeff[3];
	float	t_d[2];

	vec_cross_prod(&ray->dir, &shape->v_3d, &u);
	vec_sub(&ray->org, &shape->coordinates, &d2shape);
	vec_cross_prod(&d2shape, &shape->v_3d, &v);
	t_d[1] = t_d_calc(coeff, shape, &u, &v);
	if (t_d[1] < 0 || (-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] - sqrtf(t_d[1])) / (2 * coeff[0]) > 0)
		t_d[0] = (-coeff[1] - sqrtf(t_d[1])) / (2 * coeff[0]);
	else
		t_d[0] = (-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]);
	vec_scalar_multip(t_d[0], &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, &d2shape);
	vec_cross_prod(&shape->v_3d, &d2shape, &u);
	vec_cross_prod(&u, &shape->v_3d, nrm);
	vec_sub(pos, &shape->coordinates, &v);
	if (fabs(dot_p(&v, &shape->v_3d)) < (shape->h / 2))
		return (t_d[0]);
	return (0);
}
