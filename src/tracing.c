/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:29:23 by vbotev            #+#    #+#             */
/*   Updated: 2022/05/10 10:55:25 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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

void	set_transform(float x[][3], float y[][3], float z[][3], float angle[3])
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

t_vect	*camera_dir(t_vect *ray_dir, t_data d)
{
	float	rot_x[3][3];
	float	rot_y[3][3];
	float	rot_z[3][3];
	float	angle[3];
//	int		i;
//	int		j;

	init_mtrx(rot_x);
	init_mtrx(rot_y);
	init_mtrx(rot_z);
//	if (d.s->camera->vect_3d.z)
	angle[0] = M_PI * atan(d.s->camera->vect_3d.y / (d.s->camera->vect_3d.z));
	angle[1] = M_PI * atan(d.s->camera->vect_3d.x / (d.s->camera->vect_3d.z));
//	angle[2] = atan(d.s->camera->vect_3d.y / d.s->camera->vect_3d.x);
	angle[2] = 0;
	set_transform(rot_x, rot_y, rot_z, angle);
	vec_mat_multip(rot_x, ray_dir, ray_dir);
	vec_mat_multip(rot_y, ray_dir, ray_dir);
	vec_mat_multip(rot_z, ray_dir, ray_dir);


/*	
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			printf("%f   ", rot_x[i][j]);
		}
		printf("\n");
	}
	 i = -1;
    while (++i < 3)
    {
        j = -1;
        while (++j < 3)
        {
            printf("%f   ", rot_y[i][j]);
        }
        printf("\n");
    }
	 i = -1;
    while (++i < 3)
    {
        j = -1;
        while (++j < 3)
        {
            printf("%f   ", rot_z[i][j]);
        }
        printf("\n");
    }

	
*/

	return (ray_dir);
}

t_vect	*dir_vec(t_vect *ray_dir, int i, int j, t_data d)
{
	ray_dir->x = j - d.w / 2;
	ray_dir->y = i - d.h / 2;
	if (d.s->camera->vect_3d.z < 0)
		ray_dir->z = -d.w / (2 * tan(d.s->camera->fov / 2));
	else
		ray_dir->z = d.w / (2 * tan(d.s->camera->fov / 2));
	return (ray_dir);
}

void	math_operations(t_ray *ray, t_ray *light, t_data *d)
{
	vec_scalar_multip(0.001, &ray->nrm, &light->org);
	vec_add(&ray->pos, &light->org, &light->org);
	vec_sub(&d->s->light->coordinates, &ray->pos, &ray->pos);
	vec_dup(&ray->pos, &light->dir);
	light->dir = *normalize(&light->dir);
}

t_vect	*reflect(t_ray *l, t_vect *rfl)
{
	float	tmp;

	tmp = 2 * dot_product(&l->nrm,&l->dir);
	vec_dup(&l->nrm, rfl);
	vec_scalar_multip(tmp, rfl, rfl);
	vec_sub(rfl, &l->dir, rfl);
	return (rfl);

}

int	ray_tracing(t_data d)
{
	int		i;
	int		j;
	t_ray	ray;
	t_ray	l;
	t_vect	rfl;

	i = -1;
	vec_dup(&d.s->camera->coordinates, &ray.org);
	while (++i < d.h)
	{
		j = -1;
		while (++j < d.w)
		{
			ray.dir = *normalize(dir_vec(&ray.dir, i, j, d));
			ray.dir = *normalize(camera_dir(&ray.dir, d));
			if (sc_inter(d, &ray))
			{
				math_operations(&ray, &l, &d);
				reflect(&l, &rfl);
				if (!(sc_inter(d, &l) && (l.intr * l.intr < norm_sq(&ray.pos))))
					pixel_colors(d, &ray);
				else
					pixel_colors_shadow(d, &ray);
				my_mlx_pixel_put(&d, j, d.h - i - 1, d.s->stack->color);
			}
		}
	}
	return (0);
}
