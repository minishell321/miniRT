/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/04/19 17:40:55 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

unsigned int	dec2hex(int n)
{
	unsigned int	hex;

	hex = 0;
	hex = pow(16, 7) * (n / 16);
	hex = pow(16, 6) * (n % 16);
	hex += pow(16, 5) * (n / 16);
	hex += pow(16, 4) * (n % 16);
	hex += pow(16, 3) * (n / 16);
	hex += pow(16, 2) * (n % 16);
	hex += pow(16, 1) * (n / 16);
	hex += n % 16;
	return (hex);
}

void	pixel_colors(t_data data, t_ray *ray)
{
	double	pixel_intensity_r;
	double	pixel_intensity_g;
	double	pixel_intensity_b;
	double	*tmp;

	tmp = malloc(sizeof(double) * 3);
	tmp = vec_dup(ray->pos, tmp);
	tmp = normalize(tmp);

//  pixel_intensity_r = fmin(data.scene->stack->colors[0], data.scene->stack->colors[0] \
//      * data.scene->light->ratio * 10000 \
//      * fmax(0, dot_product(tmp, normal)) / (norm_squared(position)));
//  pixel_intensity_g = fmin(data.scene->stack->colors[1], data.scene->stack->colors[1] \
//      * data.scene->light->ratio * 10000 \
//      * fmax(0, dot_product(tmp, normal)) / (norm_squared(position)));
//  pixel_intensity_b = fmin(data.scene->stack->colors[2], data.scene->stack->colors[2] \
//      * data.scene->light->ratio * 10000 \
//      * fmax(0, dot_product(tmp, normal)) / (norm_squared(position)));

//  pixel_intensity_r = fmin(ray->sf_color[0], fmax(0, data.scene->light->ratio \
//      * 1000000 * fmax(0, dot_product(tmp,ray->nrm)) / (norm_squared(ray->pos))));
//  pixel_intensity_g = fmin(ray->sf_color[1], fmax(0, data.scene->light->ratio \
//      * 1000000 * fmax(0, dot_product(tmp,ray->nrm)) / (norm_squared(ray->pos))));
//  pixel_intensity_b = fmin(ray->sf_color[0], fmax(0, data.scene->light->ratio \
//      * 1000000 * fmax(0, dot_product(tmp,ray->nrm)) / (norm_squared(ray->pos))));

	pixel_intensity_r = fmin(ray->sf_color[0], ray->sf_color[0] \
		* data.scene->light->ratio * 5000 \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_g = fmin(ray->sf_color[1], ray->sf_color[1] \
		* data.scene->light->ratio * 5000 \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_b = fmin(ray->sf_color[2], ray->sf_color[2] \
		* data.scene->light->ratio * 5000 \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));

	data.scene->stack->color = encode_rgb((unsigned char)pixel_intensity_r, \
		(unsigned char)pixel_intensity_g, (unsigned char)pixel_intensity_b);
	free(tmp);
}

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
