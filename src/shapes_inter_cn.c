/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_inter_cn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:47:12 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/12 17:50:55 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	cn_intersect_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	float	coeff[3];
	float	t_d[2];
	float	c_angle;
	t_vect	c_crd;
	t_vect	t;
	
	c_angle = shape->diameter * M_PI / 180;
	vec_dup(&shape->coordinates, &c_crd);
	vec_sub(&ray->org, &c_crd, &c_crd);
	coeff[0] = powf(dot_product(&ray->dir, &shape->vect_3d), 2) - powf(cosf(c_angle), 2);
	coeff[1] = 2 * (dot_product(&ray->dir, &shape->vect_3d) * dot_product(&c_crd, &shape->vect_3d) - (dot_product(&ray->dir, &c_crd) * powf(cosf(c_angle), 2)));
	coeff[2] = powf(dot_product(&c_crd, &shape->vect_3d), 2) - (dot_product(&c_crd, &c_crd) * powf(cosf(c_angle), 2));
	t_d[1] = coeff[1] * coeff[1] - (4 * coeff[0] * coeff[2]);
	if (t_d[1] < 0 || (-coeff[1] - sqrt(t_d[1])) / (2 * coeff[0]) < 0)
		return (0);
	if ((-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]) > 0)
		t_d[0] = (-coeff[1] + sqrtf(t_d[1])) / (2 * coeff[0]);
	else
		t_d[0] = (-coeff[1] - sqrtf(t_d[1])) /  (2 * coeff[0]);
	vec_scalar_multip(t_d[0], &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_sub(pos, &shape->coordinates, &t);
	vec_scalar_multip(dot_product(&shape->vect_3d, &t) / dot_product(&t, &t), &t, nrm);
	vec_sub(nrm, &shape->vect_3d, nrm);
	nrm = normalize(nrm);
	if (dot_product(&t, &shape->vect_3d) > 0 && dot_product(&t, &shape->vect_3d) < shape->h)
		return (t_d[0]);
	return (0);
}

float   cn_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm)
{
	t_vect  u;
	t_vect  tmp;
	float   denom;
	float   t;
	
	vec_scalar_multip(shape->h, normalize(&shape->vect_3d), &tmp);
	vec_add(&tmp, &shape->coordinates, &u);
	vec_sub(&u, &ray->org, &tmp);
	denom = dot_product(&ray->dir, normalize(&shape->vect_3d));
	if (denom == 0)
		return (cn_intersect_open(ray,shape,pos,nrm));
	t = dot_product(&tmp, normalize(&shape->vect_3d)) / denom;
	if (t <= 0)
		return (cn_intersect_open(ray,shape,pos,nrm));
	vec_scalar_multip(t, &ray->dir, pos);
	vec_add(&ray->org, pos, pos);
	vec_assign(nrm, shape->vect_3d.x, shape->vect_3d.y, shape->vect_3d.z);
	nrm = normalize(nrm);
	vec_sub(pos, &u, &tmp);
	if (dot_product(&tmp, &tmp) <= powf(shape->h * tanf(shape->diameter * M_PI / 180), 2))
		return (t);
	else
		return (cn_intersect_open(ray,shape,pos,nrm));
}
