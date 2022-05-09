/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:17 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 09:58:52 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(t_scene *s)
{
	s->stack = NULL;
	s->amb = NULL;
	s->light = NULL;
	s->camera = NULL;
}

void	free_scene_el(t_scene *s)
{
	t_shapes	*tmp;
	t_shapes	*tmp_next;

	if (s->light)
	{
		printf("free light\n");
		free(s->light);
	}
	if (s->amb)
	{
		printf("free amb\n");
		free(s->amb);
	}
	if (s->camera)
	{
		printf("free camera\n");
		free(s->camera);
	}
	if (s->stack)
	{
		tmp = s->stack;
		while (tmp != NULL)
		{
			tmp_next = tmp->next;
			printf("free shape type: %d\n", tmp->type);
			free(tmp);
			tmp = tmp_next;
		}
	}
}

// void	print_scene(t_scene *s)
// {
// 	if (s->amb)
// 	{
// 		printf("\033[0;31mamb: \n\033[0m");
// 		printf("ambiant light ratio: %f\n", s->amb->light);
// 		printf("RGB: %d, %d ,%d\n", s->amb->colors[0], s->amb->colors[1], s->amb->colors[2]);
// 		printf("color unsigned int : %d\n", s->amb->color);
// 	}
// 	if (s->light)
// 	{
// 		printf("\033[0;31mlight: \n\033[0m");
// 		printf("light ratio de lumiosite: %f\n", s->light->ratio);
// 		printf("light coord: x = %f, y = %f, z = %f\n", s->light->coordinates.x, s->light->coordinates.y, s->light->coordinates.z);
// 	}
// 	if (s->camera)
// 	{
// 		printf("\033[0;31mcamera: \n\033[0m");
// 		printf("camera coord: x = %f, y = %f, z = %f\n", s->camera->coordinates.x, s->camera->coordinates.y, s->camera->coordinates.z);
// 		printf("vect_3d: x = %f, y= %f, z = %f\n", s->camera->vect_3d.x, s->camera->vect_3d.y, s->camera->vect_3d.z);
// 		printf("camera FOV: %f\n", s->camera->fov);
// 	}
// 	if (s->stack)
// 	{
// 		t_shapes *tmp;

// 		tmp = s->stack;
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