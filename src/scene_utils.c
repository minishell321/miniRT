/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:17 by rburri            #+#    #+#             */
/*   Updated: 2022/04/27 11:05:37 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(t_scene *scene)
{
	scene->stack = NULL;
	scene->amb_lit = NULL;
	scene->light = NULL;
	scene->camera = NULL;
}

void	free_scene_el(t_scene *scene)
{
	t_shapes	*tmp;
	t_shapes	*tmp_next;
	
	if (scene->light)
	{
		printf("free light\n");
		free(scene->light);
	}
	if (scene->amb_lit)
	{
		printf("free amb_lit\n");
		free(scene->amb_lit);
	}
	if (scene->camera)
	{
		printf("free camera\n");
		free(scene->camera);
	}
	if (scene->stack)
	{
		tmp = scene->stack;
		while (tmp != NULL)
		{
			tmp_next = tmp->next;
			printf("free : shape\n");
			free(tmp);
			tmp = tmp_next;
		}
	}
}

void	print_scene(t_scene *scene)
{
	if (scene->amb_lit)
	{
		printf("\033[0;31mamb_lit: \n\033[0m");
		printf("ambiant light ratio: %f\n", scene->amb_lit->light);
		printf("RGB: %d, %d ,%d\n", scene->amb_lit->colors[0], scene->amb_lit->colors[1], scene->amb_lit->colors[2]);
		printf("color unsigned int : %d\n", scene->amb_lit->color);
	}
	if (scene->light)
	{
		printf("\033[0;31mlight: \n\033[0m");
		printf("light ratio de lumiosite: %f\n", scene->light->ratio);
		printf("light coord: x = %f, y = %f, z = %f\n", scene->light->coordinates[0], scene->light->coordinates[1], scene->light->coordinates[2]);
	}
	if (scene->camera)
	{
		printf("\033[0;31mcamera: \n\033[0m");
		printf("camera coord: x = %f, y = %f, z = %f\n", scene->camera->coordinates[0], scene->camera->coordinates[1], scene->camera->coordinates[2]);
		printf("vect_3d: x = %f, y= %f, z = %f\n", scene->camera->vect_3d[0], scene->camera->vect_3d[1], scene->camera->vect_3d[2]);
		printf("camera FOV: %f\n", scene->camera->fov);
	}
	if (scene->stack)
	{
		t_shapes *tmp;

		tmp = scene->stack;
		while (tmp != NULL)
		{
			printf("\033[0;31mshape type: %d\n\033[0m",tmp->type);
			printf("shape coord: x = %f, y = %f, z = %f\n", tmp->coordinates[0], tmp->coordinates[1], tmp->coordinates[2]);
			printf("shape RGB: %d, %d ,%d\n", tmp->colors[0], tmp->colors[1], tmp->colors[2]);
			printf("color unsigned int : %d\n", tmp->color);
			printf("shape vect_3d: x = %f, y = %f, z = %f\n", tmp->vect_3d[0], tmp->vect_3d[1], tmp->vect_3d[2]);
			if (tmp->diameter)
				printf("shape diameter: %f\n", tmp->diameter);
			if (tmp->height)
				printf("shape height: %f\n", tmp->height);
			tmp = tmp->next;
		}
	}
}