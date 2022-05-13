/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/13 16:44:39 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vect	*dir_vec(t_vect *ray_dir, int i, int j, t_data d)
{
	ray_dir->x = j - d.w / 2;
	ray_dir->y = i - d.h / 2;
	if (d.s->camera->v_3d.z < 0)
		ray_dir->z = -d.w / (2 * tan(d.s->camera->fov / 2));
	else
		ray_dir->z = d.w / (2 * tan(d.s->camera->fov / 2));
	return (ray_dir);
}

void	math_operations(t_ray *ray, t_ray *light, t_data *d)
{
	vec_scalar_multip(0.01, &ray->nrm, &light->org);
	vec_add(&ray->pos, &light->org, &light->org);
	vec_sub(&d->s->light->coordinates, &ray->pos, &ray->pos);
	vec_dup(&ray->pos, &light->dir);
	light->dir = *normalize(&light->dir);
}

void	in_shadow_or_not(t_data *d, t_ray *l, t_ray *ray, t_specular *spec)
{
	if (!(sc_inter(*(d), l) && (l->intr * l->intr < norm_sq(&ray->pos))))
		pixel_colors(*(d), ray, spec->s);
	else
		pixel_colors_shadow(*(d), ray);
}

void	reflection_calc(t_specular *spec, t_ray *ray, t_ray *l)
{
	reflect(l, ray, &spec->rfl);
	spec->rfl = *normalize(&spec->rfl);
	spec->s = pow(fmax(0, dot_p(&spec->rfl, &ray->dir)), 15);
}

int	ray_tracing(t_data d)
{
	int			i[2];
	t_ray		ray;
	t_ray		l;
	t_specular	spec;

	i[0] = -1;
	vec_dup(&d.s->camera->coordinates, &ray.org);
	while (++i[0] < d.h)
	{
		i[1] = -1;
		while (++i[1] < d.w)
		{
			ray.dir = *normalize(dir_vec(&ray.dir, i[0], i[1], d));
			ray.dir = *normalize(camera_dir(&ray.dir, d));
			if (sc_inter(d, &ray))
			{
				math_operations(&ray, &l, &d);
				reflection_calc(&spec, &ray, &l);
				in_shadow_or_not(&d, &l, &ray, &spec);
				my_mlx_pixel_put(&d, i[1], d.h - i[0] - 1, d.s->stack->color);
			}
		}
	}
	return (0);
}
