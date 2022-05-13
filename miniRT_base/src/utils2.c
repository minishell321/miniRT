/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:42:36 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 13:51:10 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	s_trans(float x[][3], float y[][3], float z[][3], float angle[3])
{
	x[1][1] = cos(angle[0]);
	x[1][2] = -sin(angle[0]);
	x[2][1] = sin(angle[0]);
	x[2][2] = cos(angle[0]);
	y[0][0] = cos(angle[1]);
	y[0][2] = sin(angle[1]);
	y[2][0] = -sin(angle[1]);
	y[2][2] = cos(angle[1]);
	z[0][0] = cos(angle[2]);
	z[0][1] = -sin(angle[2]);
	z[1][0] = sin(angle[2]);
	z[1][1] = cos(angle[2]);
}

t_vect	*reflect(t_ray *l, t_ray *r, t_vect *rfl)
{
	float	tmp;

	tmp = (2 * dot_p(&r->nrm, &l->dir));
	vec_dup(&r->nrm, rfl);
	vec_scalar_multip(tmp, rfl, rfl);
	vec_sub(&l->dir, rfl, rfl);
	return (rfl);
}

void	shape_init(t_shapes *shape)
{
	shape->type = 0;
	shape->coordinates.x = 0;
	shape->coordinates.y = 0;
	shape->coordinates.z = 0;
	shape->v_3d.x = 0;
	shape->v_3d.y = 0;
	shape->v_3d.z = 0;
	shape->diam = 0;
	shape->h = 0;
	shape->color = 0;
	shape->colors[0] = 0;
	shape->colors[1] = 0;
	shape->colors[2] = 0;
	shape->next = NULL;
}

void	init_mtrx(float matrix[][3])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (j == i)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
}
