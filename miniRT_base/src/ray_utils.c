/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/13 15:58:18 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	mix_colors(t_ray *ray, t_data d)
{
	ray->sf_color[0] = ray->sf_color[0] * (d.s->amb->colors[0] / 255);
	ray->sf_color[1] = ray->sf_color[1] * (d.s->amb->colors[1] / 255);
	ray->sf_color[2] = ray->sf_color[2] * (d.s->amb->colors[2] / 255);
}

static void	check_max_value(float *r, float *g, float *b)
{
	if (*r > 255)
		*r = 255;
	if (*g > 255)
		*g = 255;
	if (*b > 255)
		*b = 255;
}

void	pixel_colors(t_data d, t_ray *ray, float specular)
{
	float	r;
	float	g;
	float	b;
	t_vect	tmp;

	tmp = vec_dup(&ray->pos, &tmp);
	tmp = *normalize(&tmp);
	mix_colors(ray, d);
	r = fmin(ray->sf_color[0], ray->sf_color[0] * d.s->light->ratio * L_INT \
		* fmax(0, dot_p(&tmp, &ray->nrm)) / (norm_sq(&ray->pos)));
	g = fmin(ray->sf_color[1], ray->sf_color[1] * d.s->light->ratio * L_INT \
		* fmax(0, dot_p(&tmp, &ray->nrm)) / (norm_sq(&ray->pos)));
	b = fmin(ray->sf_color[2], ray->sf_color[2] * d.s->light->ratio * L_INT \
		* fmax(0, dot_p(&tmp, &ray->nrm)) / (norm_sq(&ray->pos)));
	r = fmax(r + d.s->light->ratio * L_INT * specular, ray->sf_color[0] \
		* L_INT * d.s->amb->light * A_INT);
	g = fmax(g + d.s->light->ratio * L_INT * specular, ray->sf_color[1] \
		* L_INT * d.s->amb->light * A_INT);
	b = fmax(b + d.s->light->ratio * L_INT * specular, ray->sf_color[2] \
		* L_INT * d.s->amb->light * A_INT);
	check_max_value(&r, &g, & b);
	d.s->stack->color = encode_rgb((int)r, (int)g, (int)b);
}

void	pixel_colors_shadow(t_data d, t_ray *ray)
{
	float	r;
	float	g;
	float	b;

	mix_colors(ray, d);
	r = ray->sf_color[0] * L_INT * d.s->amb->light * A_INT;
	g = ray->sf_color[1] * L_INT * d.s->amb->light * A_INT;
	b = ray->sf_color[2] * L_INT * d.s->amb->light * A_INT;
	check_max_value(&r, &g, & b);
	d.s->stack->color = encode_rgb((int)r, \
		(int)g, (int)b);
}
