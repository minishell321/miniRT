/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:27 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 15:51:52 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	create_amb(char **split, t_scene *s)
{
	char		**sub_split;
	int			i;

	i = 0;
	s->amb = malloc(sizeof(t_amb));
	if (s->amb == NULL)
		return (1);
	s->amb->light = ft_atof(split[1]);
	if (s->amb->light > 1.0 || s->amb->light < 0.0)
		return (1);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	while (i < 3)
	{
		s->amb->colors[i] = ft_atoi(sub_split[i]);
		if (s->amb->colors[i] > 255 || s->amb->colors[i] < 0)
			return (1);
		i++;
	}
	s->amb->color = encode_rgb(s->amb->colors[0], \
		s->amb->colors[1], s->amb->colors[2]);
	ft_free_split(sub_split);
	return (0);
}

static int	create_light(char **split, t_scene *s)
{
	char	**sub_split;

	s->light = malloc(sizeof(t_light));
	if (s->light == NULL)
		return (1);
	s->light->ratio = ft_atof(split[2]);
	if (s->light->ratio > 1.0 || s->light->ratio < 0.0)
		return (1);
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	s->light->coordinates.x = ft_atof(sub_split[0]);
	s->light->coordinates.y = ft_atof(sub_split[1]);
	s->light->coordinates.z = ft_atof(sub_split[2]);
	ft_free_split(sub_split);
	return (0);
}

int	upload_scene(char **split, t_scene *s)
{
	if (!ft_strncmp(split[0], "A", 2))
	{
		if (s->amb || create_amb(split, s))
			return (1);
	}
	else if (!ft_strncmp(split[0], "C", 2))
	{
		if (s->camera || create_camera(split, s))
			return (1);
	}
	else if (!ft_strncmp(split[0], "L", 2))
	{
		if (s->light || create_light(split, s))
			return (1);
	}
	else
	{
		if (create_shape(split, s))
			return (1);
	}
	return (0);
}
