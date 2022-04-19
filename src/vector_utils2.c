/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:50:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/04/19 14:55:34 by vbotev           ###   ########.fr       */
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
