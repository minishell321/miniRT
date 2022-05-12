/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/12 11:31:00 by vbotev           ###   ########.fr       */
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
	r = fmin(ray->sf_color[0], ray->sf_color[0] \
		* d.s->light->ratio * L_INT \
		* fmax(0, dot_product(&tmp, &ray->nrm))  / (norm_sq(&ray->pos)));
	g = fmin(ray->sf_color[1], ray->sf_color[1] \
		* d.s->light->ratio * L_INT \
		* fmax(0, dot_product(&tmp, &ray->nrm)) / (norm_sq(&ray->pos)));
	b = fmin(ray->sf_color[2], ray->sf_color[2] \
		* d.s->light->ratio * L_INT \
		* fmax(0, dot_product(&tmp, &ray->nrm)) / (norm_sq(&ray->pos)));
	r = fmax(r + d.s->light->ratio * L_INT * specular * 0.15, ray->sf_color[0] * L_INT * d.s->amb->light * 0.0003);
	g = fmax(g + d.s->light->ratio * L_INT * specular * 0.15, ray->sf_color[1] * L_INT * d.s->amb->light * 0.0003);
	b = fmax(b + d.s->light->ratio * L_INT * specular * 0.15, ray->sf_color[2] * L_INT * d.s->amb->light * 0.0003);
	check_max_value(&r, &g, & b);
	d.s->stack->color = encode_rgb((int)r, \
		(int)g, (int)b);
}

void	pixel_colors_shadow(t_data d, t_ray *ray)
{
	float	r;
	float	g;
	float	b;

	mix_colors(ray, d);
	r = ray->sf_color[0] * L_INT * d.s->amb->light * 0.0003;
	g = ray->sf_color[1] * L_INT * d.s->amb->light * 0.0003;
	b = ray->sf_color[2] * L_INT * d.s->amb->light * 0.0003;
	check_max_value(&r, &g, & b);
	d.s->stack->color = encode_rgb((int)r, \
		(int)g, (int)b);
}

// unsigned int	dec2hex(int n)
// {
// 	unsigned int	hex;

// 	hex = 0;
// 	hex = pow(16, 7) * (n / 16);
// 	hex = pow(16, 6) * (n % 16);
// 	hex += pow(16, 5) * (n / 16);
// 	hex += pow(16, 4) * (n % 16);
// 	hex += pow(16, 3) * (n / 16);
// 	hex += pow(16, 2) * (n % 16);
// 	hex += pow(16, 1) * (n / 16);
// 	hex += n % 16;
// 	return (hex);
// }
/*
int	init_ray(t_ray *ray)
{
	ray->org = malloc(sizeof(double) * 3);
	ray->dir = malloc(sizeof(double) * 3);
	ray->pos = malloc(sizeof(double) * 3);
	ray->nrm = malloc(sizeof(double) * 3);
	ray->sf_color = malloc(sizeof(unsigned char) * 3);
	if (!ray->org || !ray->dir || !ray->pos || !ray->nrm || !ray->sf_color)
		return (1);
	return (0);
}

void	free_ray(t_ray *ray)
{
	free(ray->org);
	free(ray->dir);
	free(ray->pos);
	free(ray->nrm);
	free(ray->sf_color);
	free(ray);
}
*/
