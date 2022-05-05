/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/05 12:02:58 by rburri           ###   ########.fr       */
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
	ray->sf_color[0] = ray->sf_color[0] * (data.scene->amb_lit->colors[0] / 255);
	ray->sf_color[1] = ray->sf_color[1] * (data.scene->amb_lit->colors[1] / 255);
	ray->sf_color[2] = ray->sf_color[2] * (data.scene->amb_lit->colors[2] / 255);
	pixel_intensity_r = fmin(ray->sf_color[0], ray->sf_color[0] \
		* data.scene->light->ratio * LIGHT_INTENS \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_g = fmin(ray->sf_color[1], ray->sf_color[1] \
		* data.scene->light->ratio * LIGHT_INTENS \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_b = fmin(ray->sf_color[2], ray->sf_color[2] \
		* data.scene->light->ratio * LIGHT_INTENS \
		* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_r = fmax(pixel_intensity_r, ray->sf_color[0] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003);
	pixel_intensity_g = fmax(pixel_intensity_g, ray->sf_color[1] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003);
	pixel_intensity_b = fmax(pixel_intensity_b, ray->sf_color[2] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003);
	if (pixel_intensity_r > 255)
		pixel_intensity_r = 255;
	if (pixel_intensity_g > 255)
		pixel_intensity_g = 255;
	if (pixel_intensity_b > 255)
		pixel_intensity_b = 255;
	data.scene->stack->color = encode_rgb((int)pixel_intensity_r, \
		(int)pixel_intensity_g, (int)pixel_intensity_b);
	free(tmp);
}

void	pixel_colors_shadow(t_data data, t_ray *ray)
{
	double	pixel_intensity_r;
	double	pixel_intensity_g;
	double	pixel_intensity_b;

	ray->sf_color[0] = ray->sf_color[0] * (data.scene->amb_lit->colors[0] / 255);
	ray->sf_color[1] = ray->sf_color[1] * (data.scene->amb_lit->colors[1] / 255);
	ray->sf_color[2] = ray->sf_color[2] * (data.scene->amb_lit->colors[2] / 255);
	pixel_intensity_r = ray->sf_color[0] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003;
	pixel_intensity_g = ray->sf_color[1] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003;
	pixel_intensity_b = ray->sf_color[2] * LIGHT_INTENS * data.scene->amb_lit->light * 0.0003;
	if (pixel_intensity_r > 255)
		pixel_intensity_r = 255;
	if (pixel_intensity_g > 255)
		pixel_intensity_g = 255;
	if (pixel_intensity_b > 255)
		pixel_intensity_b = 255;
	data.scene->stack->color = encode_rgb((int)pixel_intensity_r, \
		(int)pixel_intensity_g, (int)pixel_intensity_b);
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
