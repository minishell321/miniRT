/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:12:34 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 13:51:10 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	assign_cam_coords(t_scene *s, char **sub_split)
{
	s->camera->coordinates.x = ft_atof(sub_split[0]);
	s->camera->coordinates.y = ft_atof(sub_split[1]);
	s->camera->coordinates.z = ft_atof(sub_split[2]);
}

static void	assign_cam_vect(t_scene *s, char **sub_split)
{
	s->camera->v_3d.x = ft_atof(sub_split[0]);
	s->camera->v_3d.y = ft_atof(sub_split[1]);
	s->camera->v_3d.z = ft_atof(sub_split[2]);
}

int	create_camera(char **split, t_scene *s)
{
	char	**sub_split;
	char	**sub_split2;

	s->camera = malloc(sizeof(t_camera));
	sub_split = ft_split(split[1], ',');
	sub_split2 = ft_split(split[2], ',');
	if (sub_split == NULL || sub_split2 == NULL || s->camera == NULL \
	|| split_len(sub_split) != 3 || split_len(sub_split2) != 3)
		return (1);
	assign_cam_coords(s, sub_split);
	assign_cam_vect(s, sub_split2);
	if (s->camera->v_3d.x < -1.0 || s->camera->v_3d.x > 1.0
		|| s->camera->v_3d.y < -1.0 || s->camera->v_3d.y > 1.0
		|| s->camera->v_3d.z < -1.0 || s->camera->v_3d.z > 1.0)
		return (1);
	ft_free_split(sub_split);
	ft_free_split(sub_split2);
	s->camera->fov = ft_atof(split[3]);
	if (s->camera->fov < 0 || s->camera->fov > 180)
		return (1);
	s->camera->fov *= M_PI / 180;
	return (0);
}

t_vect	*camera_dir(t_vect *ray_dir, t_data d)
{
	float	rot_x[3][3];
	float	rot_y[3][3];
	float	rot_z[3][3];
	float	angle[3];

	init_mtrx(rot_x);
	init_mtrx(rot_y);
	init_mtrx(rot_z);
	angle[0] = M_PI - atan(d.s->camera->v_3d.y / (d.s->camera->v_3d.z));
	angle[1] = M_PI - atan(d.s->camera->v_3d.x / (d.s->camera->v_3d.z));
	angle[2] = M_PI;
	s_trans(rot_x, rot_y, rot_z, angle);
	vec_mat_multip(rot_x, ray_dir, ray_dir);
	vec_mat_multip(rot_y, ray_dir, ray_dir);
	vec_mat_multip(rot_z, ray_dir, ray_dir);
	return (ray_dir);
}
