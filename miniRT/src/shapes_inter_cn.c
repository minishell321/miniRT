/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter_cn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:47:12 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/13 11:40:56 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	t_d_calc(float cof[3], t_ray *ray, t_shapes *shape, t_vect c_crd)
{
	float	c_angle;

	c_angle = shape->diam * M_PI / 180;
	cof[0] = powf(dot_p(&ray->dir, &shape->v_3d), 2) - powf(cosf(c_angle), 2);
	cof[1] = 2 * (dot_p(&ray->dir, &shape->v_3d) * \
		dot_p(&c_crd, &shape->v_3d) - (dot_p(&ray->dir, &c_crd) * \
		powf(cosf(c_angle), 2)));
	cof[2] = powf(dot_p(&c_crd, &shape->v_3d), 2) - (dot_p(&c_crd, &c_crd) \
		* powf(cosf(c_angle), 2));
	return (cof[1] * cof[1] - (4 * cof[0] * cof[2]));
}

float	cn_intersect_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	coeff[3];
	float	t_d[2];
	t_vect	c_crd;
	t_vect	t;

	vec_dup(&shape->coordinates, &c_crd);
	vec_sub(&ray->org, &c_crd, &c_crd);
	t_d[1] = t_d_calc(coeff, ray, shape, c_crd);
	if (t_d[1] < 0 || (-coeff[1] - sqrt(t_d[1])) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]) > 0)
		t_d[0] = (-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]);
	else
		t_d[0] = (-coeff[1] - sqrtf(t_d[1])) / (2 * coeff[0]);
	vec_scalar_multip(t_d[0], &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, &t);
	vec_scalar_multip(dot_p(&shape->v_3d, &t) / dot_p(&t, &t), &t, nrm);
	vec_sub(nrm, &shape->v_3d, nrm);
	nrm = normalize(nrm);
	if (dot_p(&t, &shape->v_3d) > 0 && dot_p(&t, &shape->v_3d) < shape->h)
		return (t_d[0]);
	return (0);
}

float	cn_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_vect	u;
	t_vect	tmp;
	float	denom;
	float	t;

	vec_scalar_multip(shape->h, normalize(&shape->v_3d), &tmp);
	vec_add(&tmp, &shape->coordinates, &u);
	vec_sub(&u, &ray->org, &tmp);
	denom = dot_p(&ray->dir, normalize(&shape->v_3d));
	if (denom == 0)
		return (cn_intersect_open(ray, shape, pos, nrm));
	t = dot_p(&tmp, normalize(&shape->v_3d)) / denom;
	if (t <= 0)
		return (cn_intersect_open(ray, shape, pos, nrm));
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->v_3d.x, shape->v_3d.y, shape->v_3d.z);
	nrm = normalize(nrm);
	vec_sub(pos, &u, &tmp);
	if (dot_p(&tmp, &tmp) <= powf(shape->h * tanf(shape->diam * M_PI / 180), 2))
		return (t);
	else
		return (cn_intersect_open(ray, shape, pos, nrm));
}
