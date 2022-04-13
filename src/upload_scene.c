/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:27 by rburri            #+#    #+#             */
/*   Updated: 2022/04/13 09:31:06 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	create_amb_lit(char **split, t_scene *scene)
{
	char		**sub_split;
	int			i;

	i = 0;
	scene->amb_lit = malloc(sizeof(t_amb_lit));
	if (scene->amb_lit == NULL)
		return (1);
	scene->amb_lit->light = ft_atof(split[1]);
	if (scene->amb_lit->light > 1.0 || scene->amb_lit->light < 0.0)
		return (1);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (1);
	while (i < 3)
	{
		scene->amb_lit->colors[i] = ft_atoi(sub_split[i]);
		if (scene->amb_lit->colors[i] > 255 || scene->amb_lit->colors[i] < 0)
			return (1);
		i++;
	}
	scene->amb_lit->color = encode_rgb(scene->amb_lit->colors[0], \
		scene->amb_lit->colors[1], scene->amb_lit->colors[2]);
	ft_free_split(sub_split);
	return (0);
}

static int	create_camera(char **split, t_scene *scene)
{
	char	**sub_split;
	char	**sub_split2;
	int		i;	

	i = 0;
	scene->camera = malloc(sizeof(t_camera));
	sub_split = ft_split(split[1], ',');
	sub_split2 = ft_split(split[2], ',');
	if (sub_split == NULL || sub_split2 == NULL || scene->camera == NULL)
		return (1);
	while (i < 3)
	{
		scene->camera->coordinates[i] = ft_atof(sub_split[i]);
		scene->camera->vect_3d[i] = ft_atof(sub_split2[i]);
		if (scene->camera->vect_3d[i] < -1.0 || scene->camera->vect_3d[i] > 1.0)
			return (1);
	}
	ft_free_split(sub_split);
	ft_free_split(sub_split2);
	scene->camera->fov = ft_atoi(split[3]);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (1);
	return (0);
}

static int	create_light(char **split, t_scene *scene)
{
	char	**sub_split;
	int		i;

	i = 0;
	scene->light = malloc(sizeof(t_light));
	if (scene->light == NULL)
		return (1);
	scene->light->ratio = ft_atof(split[2]);
	if (scene->light->ratio > 1.0 || scene->light->ratio < 0.0)
		return (1);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (1);
	while (i < 3)
	{
		scene->light->coordinates[i] = ft_atof(sub_split[i]);
		i++;
	}
	ft_free_split(sub_split);
	return (0);
}

int	upload_scene(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "A", 2))
	{
		if (create_amb_lit(split, scene))
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
	{
		if (create_shape(split, scene))
			return (1);
	}
	return (0);
}
