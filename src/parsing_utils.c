/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:08:41 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 11:40:07 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_coord(t_shapes *shape, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	shape->coordinates.x = ft_atof(sub_split[0]);
	shape->coordinates.y = ft_atof(sub_split[1]);
	shape->coordinates.z = ft_atof(sub_split[2]);
	ft_free_split(sub_split);
	return (0);
}

int	init_v_3d(t_shapes *shape, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	shape->v_3d.x = ft_atof(sub_split[0]);
	if (shape->v_3d.x < -1.0 || shape->v_3d.x > 1.0)
		return (1);
	shape->v_3d.y = ft_atof(sub_split[1]);
	if (shape->v_3d.y < -1.0 || shape->v_3d.y > 1.0)
		return (1);
	shape->v_3d.z = ft_atof(sub_split[2]);
	if (shape->v_3d.z < -1.0 || shape->v_3d.z > 1.0)
		return (1);
	ft_free_split(sub_split);
	return (0);
}

int	init_colors(t_shapes *shape, char *str)
{
	char	**sub_split;
	int		i;

	i = 0;
	sub_split = ft_split(str, ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	while (i < 3)
	{
		shape->colors[i] = ft_atoi(sub_split[i]);
		if (shape->colors[i] < 0 || shape->colors[i] > 255)
			return (1);
		i++;
	}
	shape->color = encode_rgb(shape->colors[0], shape->colors[1] \
		, shape->colors[2]);
	ft_free_split(sub_split);
	return (0);
}

void	insert_shape_at_end(t_scene *s, t_shapes *shape)
{
	t_shapes	*tmp;

	tmp = s->stack;
	if (tmp == NULL)
		s->stack = shape;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = shape;
	}
}

int	check_split_len(char **split)
{
	if (ft_strncmp(split[0], "A", 2) == 0 || \
		(ft_strncmp(split[0], "L", 2) == 0))
	{
		if (split_len(split) != 3)
			return (1);
	}
	else if (ft_strncmp(split[0], "C", 2) == 0 || \
		ft_strncmp(split[0], "sp", 2) == 0 || \
		ft_strncmp(split[0], "pl", 2) == 0)
	{
		if (split_len(split) != 4)
			return (1);
	}
	else if (ft_strncmp(split[0], "cy", 2) == 0)
	{
		if (split_len(split) != 6)
			return (1);
	}
	return (0);
}
