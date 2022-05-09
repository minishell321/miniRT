/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/09 08:09:59 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vect	*dir_vec(t_vect *ray_dir, int i, int j, t_data data)
{
	ray_dir->x = j - data.width / 2;
	ray_dir->y = i - data.height / 2;
	ray_dir->z = -data.width / (2 * tan (data.scene->camera->fov / 2));
	return (ray_dir);
}

int	ray_tracing(t_data data)
{
	int		i;
	int		j;
	t_ray	ray;
	t_ray	light;
	
	i = 0;
	vec_dup(&data.scene->camera->coordinates, &ray.org);
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
		{
			ray.dir = *normalize(dir_vec(&ray.dir, i, j, data));
			if (scene_intersection(data, &ray))
			{
				vec_scalar_multip(0.01, &ray.nrm, &light.org);
				vec_add(&ray.pos, &light.org, &light.org);
				vec_sub(&data.scene->light->coordinates, &ray.pos, &ray.pos);
				vec_dup(&ray.pos, &light.dir);
				light.dir = *normalize(&light.dir);
				if (!(scene_intersection(data, &light) && (light.intersect * light.intersect < norm_squared(&ray.pos))))
					pixel_colors(data, &ray);
				else
					pixel_colors_shadow(data, &ray);
				my_mlx_pixel_put(&data, j, data.height - i - 1, data.scene->stack->color);
			}
			j++;
		}
		i++;
	}
	return (0);
}
