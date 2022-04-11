/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:08:41 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 11:37:23 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_coord(t_shapes *shape, char *str)
{
	char **sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL)
		return (1);
    shape->coordinates[0] = ft_atof(sub_split[0]);
    shape->coordinates[1] = ft_atof(sub_split[1]);
    shape->coordinates[2] = ft_atof(sub_split[2]);
    free(sub_split);
	return (0);
}

int	init_vect_orient_3d(t_shapes *shape, char *str)
{
	char **sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL)
		return (1);
    shape->vect_orient_3d[0] = ft_atof(sub_split[0]);
	shape->vect_orient_3d[1] = ft_atof(sub_split[1]);
	shape->vect_orient_3d[2] = ft_atof(sub_split[2]);
    free(sub_split);
	return (0);
}

int	init_colors(t_shapes *shape, char *str)
{
	char **sub_split;

	sub_split = ft_split(str, ',');
	if (sub_split == NULL)
		return (1);
    shape->colors[0] = ft_atoi(sub_split[0]);
	shape->colors[1] = ft_atoi(sub_split[1]);
	shape->colors[2] = ft_atoi(sub_split[2]);
    free(sub_split);
	return (0);
}

void	insert_shape_at_end(t_scene *scene, t_shapes *shape)
{
	t_shapes *tmp;

	tmp = scene->stack;
	if (tmp == NULL)
		scene->stack = shape;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = shape;
	}
}
