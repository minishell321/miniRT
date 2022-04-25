/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:10:09 by vbotev            #+#    #+#             */
/*   Updated: 2022/04/19 17:41:52 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	norm_squared(double *crdnt)
{
	double	res;

	res = crdnt[0] * crdnt[0] + crdnt[1] * crdnt[1] + crdnt[2] * crdnt[2];
	return (res);
}

double	*normalize(double *crdnt)
{
	double	norm;

	norm = sqrt(norm_squared(crdnt));
	crdnt[0] = crdnt[0] / norm;
	crdnt[1] = crdnt[1] / norm;
	crdnt[2] = crdnt[2] / norm;
	return (crdnt);
}

double	dot_product(double *a, double *b)
{
	double	res;

	res = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return (res);
}

double	*vec_add(double *a, double *b, double *res)
{
	res[0] = a[0] + b[0];
	res[1] = a[1] + b[1];
	res[2] = a[2] + b[2];
	return (res);
}

double	*vec_sub(double *a, double *b, double *res)
{
	res[0] = a[0] - b[0];
	res[1] = a[1] - b[1];
	res[2] = a[2] - b[2];
	return (res);
}
