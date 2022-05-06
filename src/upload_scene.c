/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:27 by rburri            #+#    #+#             */
/*   Updated: 2022/05/06 13:38:22 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	create_amb(char **split, t_scene *scene)
{
	char		**sub_split;
	int			i;

	i = 0;
	scene->amb = malloc(sizeof(t_amb));
	if (scene->amb == NULL)
		return (1);
	scene->amb->light = ft_atof(split[1]);
	if (scene->amb->light > 1.0 || scene->amb->light < 0.0)
		return (1);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	while (i < 3)
	{
		scene->amb->colors[i] = ft_atoi(sub_split[i]);
		if (scene->amb->colors[i] > 255 || scene->amb->colors[i] < 0)
			return (1);
		i++;
	}
	scene->amb->color = encode_rgb(scene->amb->colors[0], \
		scene->amb->colors[1], scene->amb->colors[2]);
	ft_free_split(sub_split);
	return (0);
}

static int	create_light(char **split, t_scene *scene)
{
	char	**sub_split;

	scene->light = malloc(sizeof(t_light));
	if (scene->light == NULL)
		return (1);
	scene->light->ratio = ft_atof(split[2]);
	if (scene->light->ratio > 1.0 || scene->light->ratio < 0.0)
		return (1);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	scene->light->coordinates.x = ft_atof(sub_split[0]);
	scene->light->coordinates.y = ft_atof(sub_split[1]);
	scene->light->coordinates.z = ft_atof(sub_split[2]);
	ft_free_split(sub_split);
	return (0);
}

int	upload_scene(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "A", 2))
	{
		if (scene->amb || create_amb(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "C", 2))
	{
		if (scene->camera || create_camera(split, scene))
			return (1);
	}
	else if (!ft_strncmp(split[0], "L", 2))
	{
		if (scene->light || create_light(split, scene))
			return (1);
	}
	else
	{
		printf("create shape\n");
		if (create_shape(split, scene))
			return (1);
	}
	return (0);
}
