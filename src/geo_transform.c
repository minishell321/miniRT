/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:07:11 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/02 16:06:50 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	set_transform(t_geo_tfrm *tfrm, double *trans, double *rot, double *scale)
{
	tfrm->trans_m[0][3] = trans[0];
	tfrm->trans_m[1][3] = trans[1];
	tfrm->trans_m[2][3] = trans[2];
	tfrm->rotX_m[1][1] = cos(rot[0]);
	tfrm->rotX_m[1][2] = -sin(rot[0]);
	tfrm->rotX_m[2][1] = sin(rot[0]);
	tfrm->rotX_m[2][2] = cos(rot[0]);
	tfrm->rotY_m[0][0] = cos(rot[1]);
	tfrm->rotY_m[0][2] = sin(rot[1]);
	tfrm->rotY_m[2][0] = -sin(rot[1]);
	tfrm->rotY_m[2][2] = cos(rot[1]);
	tfrm->rotZ_m[0][0] = cos(rot[2]);
	tfrm->rotZ_m[0][1] = -sin(rot[2]);
	tfrm->rotZ_m[1][0] = sin(rot[2]);
	tfrm->rotZ_m[1][1] = cos(rot[2]);
	tfrm->scale_m[0][0] = scale[0];
	tfrm->scale_m[1][1] = scale[1];
	tfrm->scale_m[2][2] = scale[2];
	return (0);
}

int	init_matrices(t_geo_tfrm *tfrm)
{
	tfrm->trans_m = init_mtrx(tfrm->trans_m);
	tfrm->rotX_m = init_mtrx(tfrm->rotX_m);
	tfrm->rotY_m = init_mtrx(tfrm->rotY_m);
	tfrm->rotZ_m = init_mtrx(tfrm->rotZ_m);
	tfrm->scale_m = init_mtrx(tfrm->scale_m);
	tfrm->fwd = init_mtrx(tfrm->fwd);
	tfrm->bck = init_mtrx(tfrm->bck);
	if (!tfrm->trans_m || !tfrm->rotX_m || !tfrm->rotY_m || !tfrm->rotZ_m
		|| !tfrm->scale_m || !tfrm->fwd || !tfrm->bck)
		return (1);
	return (0);
}

// HANDLE LEAKS
t_geo_tfrm	*geo_transform(double *trans, double *rot, double *scale, t_geo_tfrm *tfrm)
{
//	t_geo_tfrm	*tfrm;
	double		**tmp;

	tmp = NULL;
	tfrm = malloc(sizeof(t_geo_tfrm));
//	if (tfrm == 0 || init_mtrx(tfrm->trans_m) || init_mtrx(tfrm->rotX_m)
//		|| init_mtrx(tfrm->rotY_m) || init_mtrx(tfrm->rotZ_m)
//		|| init_mtrx(tfrm->scale_m) || init_mtrx(tfrm->fwd)
//		|| init_mtrx(tfrm->bck) || set_transform(tfrm, trans, rot, scale))
	if (tfrm == 0 || init_matrices(tfrm))
		return (0);
	set_transform(tfrm, trans, rot, scale);
//	printf("AFTER INIT\n");
	tmp = init_mtrx(tmp);
	matrix_multiply(tfrm->trans_m, tfrm->rotX_m, tmp);
	matrix_multiply(tmp, tfrm->rotY_m, tfrm->fwd);
	matrix_multiply(tfrm->fwd, tfrm->rotZ_m, tmp);
	matrix_multiply(tmp, tfrm->scale_m, tfrm->fwd);
	tfrm->bck = inverse(tfrm->fwd);
    
	return (tfrm);
}
