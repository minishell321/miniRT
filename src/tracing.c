/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/09 10:01:35 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vect	*dir_vec(t_vect *ray_dir, int i, int j, t_data d)
{
	ray_dir->x = j - d.w / 2;
	ray_dir->y = i - d.h / 2;
	ray_dir->z = -d.w / (2 * tan (d.s->camera->fov / 2));
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

int	ray_tracing(t_data d)
{
	int		i;
	int		j;
	t_ray	ray;
	t_ray	l;

	i = -1;
	vec_dup(&d.s->camera->coordinates, &ray.org);
	while (++i < d.h)
	{
		j = -1;
		while (++j < d.w)
		{
			ray.dir = *normalize(dir_vec(&ray.dir, i, j, d));
			if (sc_inter(d, &ray))
			{
				math_operations(&ray, &l, &d);
				if (!(sc_inter(d, &l) && (l.intr * l.intr < norm_sq(&ray.pos))))
					pixel_colors(d, &ray);
				else
					pixel_colors_shadow(d, &ray);
				my_mlx_pixel_put(&d, j, d.h - i - 1, d.s->stack->color);
			}
		}
	}
	return (0);
}
