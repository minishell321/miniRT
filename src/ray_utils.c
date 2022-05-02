/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/02 15:28:35 by rburri           ###   ########.fr       */
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
	int lum_intensity;
	
	lum_intensity = 4000000;
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

	pixel_intensity_r = fmin(ray->sf_color[0] * lum_intensity, ray->sf_color[0] \
		* data.scene->light->ratio * lum_intensity\
		* fmax(0.2, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_g = fmin(ray->sf_color[1]* lum_intensity, ray->sf_color[1] \
		* data.scene->light->ratio * lum_intensity\
		* fmax(0.2, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_b = fmin(ray->sf_color[2]* lum_intensity, ray->sf_color[2] \
		* data.scene->light->ratio * lum_intensity\
		* fmax(0.2, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	pixel_intensity_r = pow(pixel_intensity_r, 1/2.2) ;
	pixel_intensity_g = pow(pixel_intensity_g, 1/2.2) ;
	pixel_intensity_b = pow(pixel_intensity_b, 1/2.2) ;

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
