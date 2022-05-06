/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:10:09 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/05 17:14:14 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	norm_squared(t_vect *crdnt)
{
	float	res;

	res = crdnt->x * crdnt->x + crdnt->y * crdnt->y + crdnt->z * crdnt->z;
	return (res);
}

t_vect	*normalize(t_vect *crdnt)
{
	float	norm;

	norm = sqrtf(norm_squared(crdnt));
	crdnt->x = crdnt->x / norm;
	crdnt->y = crdnt->y / norm;
	crdnt->z = crdnt->z / norm;
	return (crdnt);
}

float	dot_product(t_vect *a, t_vect *b)
{
	float	res;

	res = a->x * b->x + a->y * b->y + a->z * b->z;
	return (res);
}

t_vect	vec_add(t_vect *a, t_vect *b, t_vect *res)
{
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (*res);
}

t_vect	vec_sub(t_vect *a, t_vect *b, t_vect *res)
{
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (*res);
}
