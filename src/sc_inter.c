/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_inter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:07:41 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 08:40:02 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	add_pos_colors(t_ray *ray, t_shapes *tmp, t_vect *pos, t_vect *norm_tmp)
{
	vec_dup(pos, &ray->pos);
	vec_dup(norm_tmp, &ray->nrm);
	ray->sf_color[0] = tmp->colors[0];
	ray->sf_color[1] = tmp->colors[1];
	ray->sf_color[2] = tmp->colors[2];
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
		if (tmp->type == SP)
			ret = sphere_intersection(ray, tmp, &position_tmp, &normal_tmp);
		else if (tmp->type == PL)
			ret = plan_intersection(ray, tmp, &position_tmp, &normal_tmp);
		else if (tmp->type == CY)
			ret = cyl_intersect(ray, tmp, &position_tmp, &normal_tmp);
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
