/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:52:14 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 11:56:03 by rburri           ###   ########.fr       */
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
	printf("solit[1] = %s\n", split[1]);
	printf("amb_light light: %f\n", ft_atof(split[1]));
	printf("amb_light light: %f\n", scene->amb_light->light);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (1);
	scene->amb_light->colors[0] = ft_atoi(sub_split[0]);
	scene->amb_light->colors[1] = ft_atoi(sub_split[1]);
	scene->amb_light->colors[2] = ft_atoi(sub_split[2]);
	free(sub_split);
	return (0);
}

static int	create_camera(char **split, t_scene *scene)
{
	char	**sub_split;

	scene->camera = malloc(sizeof(t_camera));
	if (scene->camera ==  NULL)
		return (1);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (1);
	scene->camera->coordinates[0] = ft_atof(sub_split[0]);
	scene->camera->coordinates[1] = ft_atof(sub_split[1]);
	scene->camera->coordinates[2] = ft_atof(sub_split[2]);
	free(sub_split);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (1);
	scene->camera->vect_orient_3d[0] = ft_atof(sub_split[0]);
	scene->camera->vect_orient_3d[1] = ft_atof(sub_split[1]);
	scene->camera->vect_orient_3d[2] = ft_atof(sub_split[2]);
	free(sub_split);
	scene->camera->fov = ft_atoi(split[3]);
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
	scene->light->coordinates[0] = ft_atof(sub_split[0]);
	scene->light->coordinates[1] = ft_atof(sub_split[1]);
	scene->light->coordinates[2] = ft_atof(sub_split[2]);
	free(sub_split);
	return (0);
}

int	upload_scene(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "A", 2))
	{
		printf("upload A\n");
		if (create_amb_light(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "C", 2))
	{
		printf("upload C\n");
		if (create_camera(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "L", 2))
	{
		printf("upload L\n");
		if (create_light(split, scene))
			return (1);
	}
	else
	{
		printf("upload Shape\n");
		if (create_shape(split, scene))
			return (1);
	}
	return (0);
}
