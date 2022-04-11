/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:52:14 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 08:08:38 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	create_amb_light(char **split, t_scene *scene)
{
	char		**sub_split;

	scene->amb_light = malloc(sizeof(t_amb_light));
	if (scene->amb_light == NULL)
		return (1);
	scene->amb_light->light = ft_atof(split[1]);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (1);
	scene->amb_light->color.r = ft_atoi(sub_split[0]);
	scene->amb_light->color.g = ft_atoi(sub_split[1]);
	scene->amb_light->color.b = ft_atoi(sub_split[2]);
	free(sub_split);
	return (0);
}

static int	create_camera(char **split, t_scene *scene)
{
	char	**sub_split;

	scene->camera = malloc(sizeof(t_camera));
	if (scene->camera ==  NULL)
		return (1);
	sub_split = ft_split(split[0], ',');
	if (sub_split == NULL)
		return (1);
	scene->camera->coord->x = ft_atof(sub_split[0]);
	scene->camera->coord->y = ft_atof(sub_split[1]);
	scene->camera->coord->z = ft_atof(sub_split[2]);
	free(sub_split);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (1);
	scene->camera->vect_orient_3d->x = ft_atof(sub_split[0]);
	scene->camera->vect_orient_3d->y = ft_atof(sub_split[1]);
	scene->camera->vect_orient_3d->z = ft_atof(sub_split[2]);
	free(sub_split);
	scene->camera->fov = ft_atoi(split[2]);
	return (0);
}

static int	create_light(char **split, t_scene *scene)
{
	char	**sub_split;

	scene->light = malloc(sizeof(t_light));
	if (scene->light == NULL)
		return (1);
	scene->light->ratio = ft_atof(split[2]);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (1);
	scene->light->coord->x = ft_atof(sub_split[0]);
	scene->light->coord->y = ft_atof(sub_split[1]);
	scene->light->coord->z = ft_atof(sub_split[2]);
	free(sub_split);
	return (0);
}

int	upload_scene(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "A", 2))
	{
		if (create_amb_light(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "C", 2))
	{
		if (create_camera(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "L", 2))
	{
		if (create_light(split, scene))
			return (1);
	}
	else
		if (create_shape(split, scene))
			return (1);
	return (0);
}
