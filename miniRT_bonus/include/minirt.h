/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 14:01:54 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "basic_struct.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
// printf perror strerror
# include <stdlib.h>
// malloc free
# include <fcntl.h>
//open
# include <unistd.h>
// close read write
# define WIDTH 1250
# define HEIGHT 1250
# define L_INT 800
# define SP 1
# define PL 2
# define CY 3
# define CN 4

// int 	parse_scene(t_shape *shape, char *file);
// MLX_UTILS.C
void	my_mlx_pixel_put(t_data *d, int x, int y, unsigned int color);

// UTILS.C
int		encode_rgb(int r, int g, int b);
void	ft_error(void);
int		my_close(int keycode, t_data *d);
int		close_win(t_data *d);
void	init_data(t_data *d, t_scene *s);
void	ft_err(char *str);
// UTILS2.C
int		split_len(char **split);
void	s_trans(float x[][3], float y[][3], float z[][3], float angle[3]);
t_vect	*reflect(t_ray *l, t_ray *r, t_vect *rfl);
void	shape_init(t_shapes *shape);
void	init_mtrx(float matrix[][3]);
// PARSING.C
int		read_file(t_scene *s, char *file);
// PARSING_UTILS.C
int		init_v_3d(t_shapes *shape, char *str);
int		init_colors(t_shapes *shape, char *str);
int		init_coord(t_shapes *shape, char *str);
void	insert_shape_at_end(t_scene *s, t_shapes *shape);
int		check_split_len(char **split);
// SCENE_UTILS.C
void	init_scene(t_scene *s);
void	print_scene(t_scene *s);
void	free_scene_el(t_scene *s);
void	check_scene_compete(t_data *d);
// FT_ATOF.C
double	ft_atof(char *str);
// UPLOAD_SCENE.C
int		upload_scene(char **split, t_scene *s);
// UPLOAD_SCENE_UTILS.C
int		create_camera(char **split, t_scene *s);
t_vect	*camera_dir(t_vect *ray_dir, t_data d);
// CREATE_SHAPE.C
int		create_shape(char **split, t_scene *s);
// VECTOR_UTILS.C
float	norm_sq(t_vect *crdnt);
t_vect	*normalize(t_vect *crdnt);
float	dot_p(t_vect *a, t_vect *b);
t_vect	vec_add(t_vect *a, t_vect *b, t_vect *res);
t_vect	vec_sub(t_vect *a, t_vect *b, t_vect *res);
// VECTOR_UTILS2.C
t_vect	vec_scalar_multip(float scalar, t_vect *vec, t_vect *res);
t_vect	vec_dup(t_vect *vec, t_vect *dup);
t_vect	vec_assign(t_vect *vec, float x, float y, float z);
t_vect	vec_mat_multip(float matrix[][3], t_vect *vec, t_vect *res);
t_vect	vec_cross_prod(t_vect *a, t_vect *b, t_vect *res);
// TRACING.C
t_vect	*dir_vec(t_vect *ray_dir, int i, int j, t_data d);
int		ray_tracing(t_data d);
// SC_INTER.C
int		sc_inter(t_data d, t_ray *ray);
// SHAPES_INTERSECTION.C
float	plan_inter(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float	cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float	cyl_inter_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float	sphere_inter(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
// SHAPES_INTER_CN.C
float	cn_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
// SHAPES_INTER_CY.C
float	cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
// SHAPES_INTER_CY_OPEN.C
float	cyl_inter_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
//RAY_UTILS.C
void	pixel_colors(t_data d, t_ray *ray, float specular);
void	pixel_colors_shadow(t_data d, t_ray *ray);
int		init_ray(t_ray *ray);
void	free_ray(t_ray *ray);
#endif
