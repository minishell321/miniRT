/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:50:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/09 15:56:45 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vect	vec_scalar_multip(float scalar, t_vect *vec, t_vect *res)
{
	res->x = scalar * vec->x;
	res->y = scalar * vec->y;
	res->z = scalar * vec->z;
	return (*res);
}

t_vect	vec_dup(t_vect *vec, t_vect *dup)
{
	dup->x = vec->x;
	dup->y = vec->y;
	dup->z = vec->z;
	return (*dup);
}

t_vect	vec_assign(t_vect *vec, float x_crd, float y_crd, float z_crd)
{
	vec->x = x_crd;
	vec->y = y_crd;
	vec->z = z_crd;
	return (*vec);
}

t_vect	vec_mat_multip(float matrix[][3], t_vect *vec, t_vect *res)
{
	float	sum;
	float	tmp[3];
	float	res_tmp[3];
	int		i;
	int		j;

//	vec_dup(vec, &tmp);
	tmp[0] = vec->x;
	tmp[1] = vec->y;
	tmp[2] = vec->z;
//	tmp[3] = 1;
	sum = 0;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			sum += matrix[i][j] * tmp[j];
		}
		res_tmp[i] = sum;
		sum = 0;
	}
//	vec_dup(&res_tmp, res);
	res->x = res_tmp[0];
	res->y = res_tmp[1];
	res->z = res_tmp[2];
	return (*res);
}

t_vect	vec_cross_prod(t_vect *a, t_vect *b, t_vect *res)
{
	res->x = a->y * b->z - (a->z * b->y);
	res->y = a->z * b->x - (a->x * b->z);
	res->z = a->x * b->y - (a->y * b->x);
	return (*res);
}
