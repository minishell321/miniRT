/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:17 by rburri            #+#    #+#             */
/*   Updated: 2022/05/06 13:38:22 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(t_scene *scene)
{
	scene->stack = NULL;
	scene->amb = NULL;
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
	if (scene->amb)
	{
		printf("free amb\n");
		free(scene->amb);
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
			printf("free shape type: %d\n", tmp->type);
			free(tmp);
			tmp = tmp_next;
		}
	}
}

// void	print_scene(t_scene *scene)
// {
// 	if (scene->amb)
// 	{
// 		printf("\033[0;31mamb: \n\033[0m");
// 		printf("ambiant light ratio: %f\n", scene->amb->light);
// 		printf("RGB: %d, %d ,%d\n", scene->amb->colors[0], scene->amb->colors[1], scene->amb->colors[2]);
// 		printf("color unsigned int : %d\n", scene->amb->color);
// 	}
// 	if (scene->light)
// 	{
// 		printf("\033[0;31mlight: \n\033[0m");
// 		printf("light ratio de lumiosite: %f\n", scene->light->ratio);
// 		printf("light coord: x = %f, y = %f, z = %f\n", scene->light->coordinates.x, scene->light->coordinates.y, scene->light->coordinates.z);
// 	}
// 	if (scene->camera)
// 	{
// 		printf("\033[0;31mcamera: \n\033[0m");
// 		printf("camera coord: x = %f, y = %f, z = %f\n", scene->camera->coordinates.x, scene->camera->coordinates.y, scene->camera->coordinates.z);
// 		printf("vect_3d: x = %f, y= %f, z = %f\n", scene->camera->vect_3d.x, scene->camera->vect_3d.y, scene->camera->vect_3d.z);
// 		printf("camera FOV: %f\n", scene->camera->fov);
// 	}
// 	if (scene->stack)
// 	{
// 		t_shapes *tmp;

// 		tmp = scene->stack;
// 		while (tmp != NULL)
// 		{
// 			printf("\033[0;31mshape type: %d\n\033[0m",tmp->type);
// 			printf("shape coord: x = %f, y = %f, z = %f\n", tmp->coordinates.x, tmp->coordinates.y, tmp->coordinates.z);
// 			printf("shape RGB: %d, %d ,%d\n", tmp->colors[0], tmp->colors[1], tmp->colors[2]);
// 			printf("color unsigned int : %d\n", tmp->color);
// 			printf("shape vect_3d: x = %f, y = %f, z = %f\n", tmp->vect_3d.x, tmp->vect_3d.y, tmp->vect_3d.z);
// 			if (tmp->diameter)
// 				printf("shape diameter: %f\n", tmp->diameter);
// 			if (tmp->height)
// 				printf("shape height: %f\n", tmp->height);
// 			tmp = tmp->next;
// 		}
// 	}
// }