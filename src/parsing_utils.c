/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:08:41 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 09:58:44 by rburri           ###   ########.fr       */
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

int	init_vect_3d(t_shapes *shape, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL || split_len(sub_split) != 3)
		return (1);
	shape->vect_3d.x = ft_atof(sub_split[0]);
	if (shape->vect_3d.x < -1.0 || shape->vect_3d.x > 1.0)
		return (1);
	shape->vect_3d.y = ft_atof(sub_split[1]);
	if (shape->vect_3d.y < -1.0 || shape->vect_3d.y > 1.0)
		return (1);
	shape->vect_3d.z = ft_atof(sub_split[2]);
	if (shape->vect_3d.z < -1.0 || shape->vect_3d.z > 1.0)
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
