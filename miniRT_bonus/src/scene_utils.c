/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 07:50:17 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 16:35:18 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(t_scene *s)
{
	s->stack = NULL;
	s->amb = NULL;
	s->light = NULL;
	s->camera = NULL;
}

void	free_scene_el(t_scene *s)
{
	t_shapes	*tmp;
	t_shapes	*tmp_next;

	if (s->light)
		free(s->light);
	if (s->amb)
		free(s->amb);
	if (s->camera)
		free(s->camera);
	if (s->stack)
	{
		tmp = s->stack;
		while (tmp != NULL)
		{
			tmp_next = tmp->next;
			free(tmp);
			tmp = tmp_next;
		}
	}
}

void	check_scene_compete(t_data *d)
{
	if (!d->s->amb || !d->s->light || !d->s->camera)
	{
		free_scene_el(d->s);
		ft_err(" Scene incomplete");
	}
}
