/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:37:50 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/05 10:37:46 by rburri           ###   ########.fr       */
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
	double sum1;
	double sum2;
	double sum3;
	double sum4;
	double sum5;
	double sum6;
	
	lum_intensity = 1000;
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



	ray->sf_color[0] = ray->sf_color[0] * (data.scene->amb_lit->colors[0] / 255);
	ray->sf_color[1] = ray->sf_color[1] * (data.scene->amb_lit->colors[1] / 255);
	ray->sf_color[2] = ray->sf_color[2] * (data.scene->amb_lit->colors[2] / 255);
	sum1 = ray->sf_color[0] * lum_intensity * data.scene->light->ratio * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	sum2 = ray->sf_color[1] * lum_intensity * data.scene->light->ratio * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	sum3 = ray->sf_color[2] * lum_intensity * data.scene->light->ratio * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	sum4 = ray->sf_color[0] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	sum5 = ray->sf_color[1] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	sum6 = ray->sf_color[2] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	sum1 = fmax(sum1, sum4);
	sum2 = fmax(sum2, sum5);
	sum3 = fmax(sum3, sum6);
	// sum1 = ray->sf_color[0] * data.scene->light->ratio * lum_intensity * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// sum2 = ray->sf_color[1] * data.scene->light->ratio * lum_intensity * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// sum3 = ray->sf_color[2] * data.scene->light->ratio * lum_intensity * (fmax(0.0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// pixel_intensity_r = (sum1 + data.scene->amb_lit->colors[0] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_g = (sum2 + data.scene->amb_lit->colors[1] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_b = (sum3 + data.scene->amb_lit->colors[2] * data.scene->amb_lit->light) / 2;

	pixel_intensity_r = sum1;
	pixel_intensity_g = sum2;
	pixel_intensity_b = sum3;
	if (pixel_intensity_r > 255)
		pixel_intensity_r = 255;
	if (pixel_intensity_g > 255)
		pixel_intensity_g = 255;
	if (pixel_intensity_b > 255)
		pixel_intensity_b = 255;

	
	// pixel_intensity_r = fmin((double)ray->sf_color[0] * lum_intensity, sum1);
	// pixel_intensity_g = fmin((double)ray->sf_color[1] * lum_intensity, sum2);
	// pixel_intensity_b = fmin((double)ray->sf_color[2] * lum_intensity, sum3);
	

	// data.scene->stack->color = encode_rgb((unsigned char)pixel_intensity_r, \
	// 	(unsigned char)pixel_intensity_g, (unsigned char)pixel_intensity_b);
	// free(tmp);

	// pixel_intensity_r = fmin(ray->sf_color[0], ray->sf_color[0] \
	// * data.scene->light->ratio * 5000000 \
	// * fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// pixel_intensity_g = fmin(ray->sf_color[1], ray->sf_color[1] \
	// 	* data.scene->light->ratio * 5000000 \
	// 	* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// pixel_intensity_b = fmin(ray->sf_color[2], ray->sf_color[2] \
	// 	* data.scene->light->ratio * 5000000 \
	// 	* fmax(0, dot_product(tmp, ray->nrm)) / (norm_squared(ray->pos)));
	// pixel_intensity_r = (pixel_intensity_r) + (data.scene->amb_lit->colors[0] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_g = (pixel_intensity_g) + (data.scene->amb_lit->colors[1] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_b = (pixel_intensity_b) + (data.scene->amb_lit->colors[2] * data.scene->amb_lit->light) / 2;
	
	// pixel_intensity_r = (pixel_intensity_r) + (data.scene->amb_lit->colors[0] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_g = (pixel_intensity_g) + (data.scene->amb_lit->colors[1] * data.scene->amb_lit->light) / 2;
	// pixel_intensity_b = (pixel_intensity_b) + (data.scene->amb_lit->colors[2] * data.scene->amb_lit->light) / 2;

	// pixel_intensity_r = pow(pixel_intensity_r, 1/2.2) ;
	// pixel_intensity_g = pow(pixel_intensity_g, 1/2.2) ;
	// pixel_intensity_b = pow(pixel_intensity_b, 1/2.2) ;
	
	// data.scene->stack->color = encode_rgb(ray->sf_color[0], \
	// 	ray->sf_color[1], ray->sf_color[2]);
		
	data.scene->stack->color = encode_rgb((int)pixel_intensity_r, \
		(int)pixel_intensity_g, (int)pixel_intensity_b);
	free(tmp);
}

void	pixel_colors_shadow(t_data data, t_ray *ray)
{
	double	pixel_intensity_r;
	double	pixel_intensity_g;
	double	pixel_intensity_b;
	double	*tmp;
	int lum_intensity;
	double sum1;
	double sum2;
	double sum3;
	
	lum_intensity = 1000;
	tmp = malloc(sizeof(double) * 3);
	tmp = vec_dup(ray->pos, tmp);
	tmp = normalize(tmp);

	ray->sf_color[0] = ray->sf_color[0] * (data.scene->amb_lit->colors[0] / 255);
	ray->sf_color[1] = ray->sf_color[1] * (data.scene->amb_lit->colors[1] / 255);
	ray->sf_color[2] = ray->sf_color[2] * (data.scene->amb_lit->colors[2] / 255);
	sum1 = ray->sf_color[0] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	sum2 = ray->sf_color[1] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	sum3 = ray->sf_color[2] * lum_intensity * data.scene->amb_lit->light * 0.0003;
	pixel_intensity_r = sum1;
	pixel_intensity_g = sum2;
	pixel_intensity_b = sum3;
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
