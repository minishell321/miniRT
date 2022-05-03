/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:50:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/03 11:32:40 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	*vec_scalar_multip(double scalar, double *vec, double *res)
{
	res[0] = scalar * vec[0];
	res[1] = scalar * vec[1];
	res[2] = scalar * vec[2];
	return (res);
}

double	*vec_dup(double *vec, double *dup)
{
	dup[0] = vec[0];
	dup[1] = vec[1];
	dup[2] = vec[2];
	return (dup);
}

double	*vec_assign(double *vec, double x, double y, double z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	return (vec);
}

double	*vec_mat_multip(double **matrix, double *vec, double *res)
{
	int	i;
	int	j;
	double	sum;
	double	tmp[4];
	double	res_tmp[4];

	tmp[0] = vec[0];
	tmp[1] = vec[1];
	tmp[2] = vec[2];
	tmp[3] = 1;
	sum = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			sum += matrix[i][j] * tmp[j];
		}
		res_tmp[i] = sum;
		sum = 0;
	}
	res[0] = res_tmp[0];
	res[1] = res_tmp[1];
	res[2] = res_tmp[2];
	return (res);
}

double	*vec_cross_prod(double *a, double *b, double *res)
{
	res[0] = a[1] * b[2] - (a[2] * b[1]);
	res[1] = a[2] * b[0] - (a[0] * b[2]);
	res[2] = a[0] * b[1] - (a[1] * b[0]);
	return (res);
}
