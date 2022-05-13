/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_inter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:07:41 by rburri            #+#    #+#             */
/*   Updated: 2022/05/12 14:30:53 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	add_pos_colors(t_ray *ray, t_shapes *tmp, t_vect *pos, t_vect *norm)
{
	vec_dup(pos, &ray->pos);
	vec_dup(norm, &ray->nrm);
	ray->sf_color[0] = tmp->colors[0];
	ray->sf_color[1] = tmp->colors[1];
	ray->sf_color[2] = tmp->colors[2];
}

float	shapes_intr(t_ray *ray, t_shapes *tmp, t_vect *pos, t_vect *nrm)
{
	float	ret;

	ret = 0;
	if (tmp->type == SP)
		ret = sphere_inter(ray, tmp, pos, nrm);
	else if (tmp->type == PL)
		ret = plan_inter(ray, tmp, pos, nrm);
	else if (tmp->type == CY)
		ret = cyl_intersect(ray, tmp, pos, nrm);
	else if (tmp->type == CN)
		ret = cn_intersect(ray, tmp, pos, nrm);
	return (ret);
}

int	sc_inter(t_data d, t_ray *ray)
{
	int			has_intersect;
	t_shapes	*tmp;
	t_vect		position_tmp;
	t_vect		normal_tmp;
	float		ret;

	ray->intr = 2147483647;
	has_intersect = 0;
	tmp = d.s->stack;
	while (tmp)
	{
		ret = shapes_intr(ray, tmp, &position_tmp, &normal_tmp);
		if (ret && ret < ray->intr)
		{
			has_intersect = 1;
			ray->intr = ret;
			add_pos_colors(ray, tmp, &position_tmp, &normal_tmp);
		}
		tmp = tmp->next;
	}
	return (has_intersect);
}
