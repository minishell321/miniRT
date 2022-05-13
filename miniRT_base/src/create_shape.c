/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:12:12 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 14:45:24 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	create_plan(t_scene *s, char **split)
{
	t_shapes	*shape;

	shape = malloc(sizeof(t_shapes));
	if (shape == NULL)
		return (1);
	shape_init(shape);
	shape->type = PL;
	if (init_coord(shape, split[1]) == 1)
		return (1);
	if (init_v_3d(shape, split[2]) == 1)
		return (1);
	if (init_colors(shape, split[3]) == 1)
		return (1);
	shape->next = NULL;
	insert_shape_at_end(s, shape);
	return (0);
}

static int	create_sphere(t_scene *s, char **split)
{
	t_shapes	*shape;

	shape = malloc(sizeof(t_shapes));
	if (shape == NULL)
		return (1);
	shape_init(shape);
	shape->type = SP;
	if (init_coord(shape, split[1]) == 1)
		return (1);
	shape->diam = ft_atof(split[2]);
	if (init_colors(shape, split[3]) == 1)
		return (1);
	shape->next = NULL;
	shape->h = 0;
	insert_shape_at_end(s, shape);
	return (0);
}

static int	create_cylinder(t_scene *s, char **split)
{
	t_shapes	*shape;

	shape = malloc(sizeof(t_shapes));
	if (shape == NULL)
		return (1);
	shape_init(shape);
	shape->type = CY;
	if (init_coord(shape, split[1]) == 1)
		return (1);
	if (init_v_3d(shape, split[2]) == 1)
		return (1);
	if (init_colors(shape, split[5]) == 1)
		return (1);
	shape->diam = ft_atof(split[3]);
	shape->h = ft_atof(split[4]);
	shape->next = NULL;
	insert_shape_at_end(s, shape);
	return (0);
}

int	create_shape(char **split, t_scene *s)
{
	if (!ft_strncmp(split[0], "sp", 3))
	{
		if (create_sphere(s, split) == 1)
			return (1);
	}
	if (!ft_strncmp(split[0], "cy", 3))
	{
		if (create_cylinder(s, split) == 1)
			return (1);
	}
	if (!ft_strncmp(split[0], "pl", 3))
	{
		if (create_plan(s, split) == 1)
			return (1);
	}
	return (0);
}
