/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:12:34 by rburri            #+#    #+#             */
/*   Updated: 2022/05/06 13:19:12 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	assign_cam_coords(t_scene *scene, char **sub_split)
{
	scene->camera->coordinates.x = ft_atof(sub_split[0]);
	scene->camera->coordinates.y = ft_atof(sub_split[1]);
	scene->camera->coordinates.z = ft_atof(sub_split[2]);
}

static void	assign_cam_vect(t_scene *scene, char **sub_split)
{
	scene->camera->vect_3d.x = ft_atof(sub_split[0]);
	scene->camera->vect_3d.y = ft_atof(sub_split[1]);
	scene->camera->vect_3d.z = ft_atof(sub_split[2]);
}

int	create_camera(char **split, t_scene *scene)
{
	char	**sub_split;
	char	**sub_split2;

	scene->camera = malloc(sizeof(t_camera));
	sub_split = ft_split(split[1], ',');
	sub_split2 = ft_split(split[2], ',');
	if (sub_split == NULL || sub_split2 == NULL || scene->camera == NULL \
	|| split_len(sub_split) != 3 || split_len(sub_split2) != 3)
		return (1);
	assign_cam_coords(scene, sub_split);
	assign_cam_vect(scene, sub_split2);
	if (scene->camera->vect_3d.x < -1.0 || scene->camera->vect_3d.x > 1.0
		|| scene->camera->vect_3d.y < -1.0 || scene->camera->vect_3d.y > 1.0
		|| scene->camera->vect_3d.z < -1.0 || scene->camera->vect_3d.z > 1.0)
		return (1);
	ft_free_split(sub_split);
	ft_free_split(sub_split2);
	scene->camera->fov = ft_atof(split[3]);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (1);
	scene->camera->fov *= M_PI / 180;
	return (0);
}
