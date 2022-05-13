/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter_cy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:43:28 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 12:36:37 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_temp_val(t_3vect *tmp_v, t_shapes *shape, t_ray *ray)
{
	vec_scalar_multip(shape->h / 2, normalize(&shape->v_3d), &tmp_v->tmp);
	vec_add(&tmp_v->tmp, &shape->coordinates, &tmp_v->u);
	vec_sub(&shape->coordinates, &tmp_v->tmp, &tmp_v->v);
	vec_sub(&tmp_v->u, &ray->org, &tmp_v->tmp);
}

void	asign_d_t_min(float t[3], float d_t_min[2])
{
	if (t[1] < t[2])
		d_t_min[1] = t[1];
	else
		d_t_min[1] = t[2];
}

void	calc_norm(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->v_3d.x, shape->v_3d.y, shape->v_3d.z);
	nrm = normalize(nrm);
}

float	cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_3vect	tmp_v;
	float	d_t_min[2];
	float	t[3];

	init_temp_val(&tmp_v, shape, ray);
	d_t_min[0] = dot_p(&ray->dir, &shape->v_3d);
	if (d_t_min[0] == 0)
		return (cyl_inter_open(ray, shape, pos, nrm));
	t[1] = dot_p(&tmp_v.tmp, normalize(&shape->v_3d)) / d_t_min[0];
	vec_sub(&tmp_v.v, &ray->org, &tmp_v.tmp);
	t[2] = dot_p(&tmp_v.tmp, normalize(&shape->v_3d)) / d_t_min[0];
	if (t[1] <= 0 || t[2] <= 0)
		return (cyl_inter_open(ray, shape, pos, nrm));
	asign_d_t_min(t, d_t_min);
	vec_scalar_multip(d_t_min[1], &ray->dir, pos);
	calc_norm(ray, shape, pos, nrm);
	if (t[1] > t[2])
		vec_scalar_multip(-1, nrm, nrm);
	vec_sub(pos, &tmp_v.u, &tmp_v.tmp);
	vec_sub(pos, &tmp_v.v, &tmp_v.u);
	if (dot_p(&tmp_v.tmp, &tmp_v.tmp) <= (shape->diam * shape->diam / 4)
		|| dot_p(&tmp_v.u, &tmp_v.u) <= (shape->diam * shape->diam / 4))
		return (d_t_min[1]);
	else
		return (cyl_inter_open(ray, shape, pos, nrm));
}
