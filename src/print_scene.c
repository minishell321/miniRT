/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:44:37 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 11:44:47 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

void	init_scene(t_scene *scene)
{
	scene->stack = NULL;
	scene->amb_light = NULL;
	scene->light = NULL;
	scene->camera = NULL;
}


void	print_scene(t_scene *scene)
{
	if (scene->amb_light)
	{
		printf("ambiant light ratio: %f\n", scene->amb_light->light);
		printf("RGB: %d, %d ,%d\n", scene->amb_light->colors[0], scene->amb_light->colors[1], scene->amb_light->colors[2]);
	}
	if (scene->light)
	{
		printf("light ratio de lumiosite: %f\n", scene->light->ratio);
		printf("light coord: x= %f, y= %f, z= %f\n", scene->light->coordinates[0], scene->light->coordinates[1], scene->light->coordinates[2]);
	}
	if (scene->camera)
	{
		printf("camera coord: x= %f, y= %f, z= %f\n", scene->camera->coordinates[0], scene->camera->coordinates[1], scene->camera->coordinates[2]);
		printf("vect_orient_3d: x= %f, y= %f, z= %f\n", scene->camera->vect_orient_3d[0], scene->camera->vect_orient_3d[1], scene->camera->vect_orient_3d[2]);
		printf("camera FOV: %d\n", scene->camera->fov);
	}
	if (scene->stack)
	{
		t_shapes *tmp;

		tmp = scene->stack;
		while (tmp != NULL)
		{
			printf("shape type: %s\n",tmp->type);
			printf("shape coord: x= %f, y= %f, z= %f\n", tmp->coordinates[0], tmp->coordinates[1], tmp->coordinates[2]);
			printf("shape RGB: %d, %d ,%d\n", tmp->colors[0], tmp->colors[1], tmp->colors[2]);
			printf("shape vect_orient_3d: x= %f, y= %f, z= %f\n", tmp->vect_orient_3d[0], tmp->vect_orient_3d[1], tmp->vect_orient_3d[2]);
			if (tmp->diameter)
				printf("shape diameter: %f\n", tmp->diameter);
			if (tmp->height)
				printf("shape height: %f\n", tmp->height);
			tmp = tmp->next;
		}
	}
}

void	free_scene_el(t_scene *scene)
{
	t_shapes *tmp;
	t_shapes *tmp_next;

	if (scene->light)
		free(scene->light);
	if (scene->amb_light)
		free(scene->amb_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->stack)
	{
		tmp = scene->stack;
		while (tmp != NULL)
		{
			if (tmp->next)
				tmp_next = tmp->next;
			free(tmp->type);
			free(tmp);
			if (tmp->next == NULL)
				tmp = NULL;
			else
				tmp = tmp_next;
		}
	}
}