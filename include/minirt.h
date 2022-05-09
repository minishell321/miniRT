/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/05/09 08:12:40 by rburri           ###   ########.fr       */
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
# define L_INT 1000
# define SP 1
# define PL 2
# define CY 3

// int 	parse_scene(t_shape *shape, char *file);
// MLX_UTILS.C
void			my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);

// UTILS.C
unsigned int	encode_rgb(int r, int g, int b);
void			ft_error(void);
int				my_close(int keycode, t_data *data);
int				close_win(t_data *data);
void			init_data(t_data *data, t_scene *scene);

// UTILS2.C
int				split_len(char **split);

// PARSING_UTILS.C
int				init_vect_3d(t_shapes *shape, char *str);
int				init_colors(t_shapes *shape, char *str);
int				init_coord(t_shapes *shape, char *str);
void			insert_shape_at_end(t_scene *scene, t_shapes *shape);

// SCENE_UTILS.C
void			init_scene(t_scene *scene);
void			print_scene(t_scene *scene);
void			free_scene_el(t_scene *scene);

// FT_ATOF.C
double			ft_atof(char *str);

// PARSING.C
int				read_file(t_scene *scene, char *file);

// UPLOAD_SCENE.C
int				upload_scene(char **split, t_scene *scene);
// UPLOAD_SCENE_UTILS.C
int				create_camera(char **split, t_scene *scene);
// CREATE_SHAPE.C
int				create_shape(char **split, t_scene *scene);
// VECTOR_UTILS.C
float			norm_squared(t_vect *crdnt);
t_vect			*normalize(t_vect *crdnt);
float			dot_product(t_vect *a, t_vect *b);
t_vect 			vec_add(t_vect *a, t_vect *b, t_vect *res);
t_vect			vec_sub(t_vect *a, t_vect *b, t_vect *res);
// VECTOR_UTILS2.C
t_vect			vec_scalar_multip(float scalar, t_vect *vec, t_vect *res);
t_vect			vec_dup(t_vect *vec, t_vect *dup);
t_vect			vec_assign(t_vect *vec, float x, float y, float z);
double			*vec_mat_multip(double **matrix, double *vec, double *res);
t_vect			vec_cross_prod(t_vect *a, t_vect *b, t_vect *res);
// TRACING.C
t_vect			*dir_vec(t_vect *ray_dir, int i, int j, t_data data);
int				ray_tracing(t_data data);
// SCENE_INTERSECTION.C
int				scene_intersection(t_data data, t_ray *ray);
void			add_pos_colors(t_ray *ray, t_shapes *tmp, t_vect *pos, t_vect *norm_tmp);

// SHAPES_INTERSECTION.C
float			plan_intersection(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float			cyl_intersect(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float			cyl_intersect_open(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);
float			sphere_intersection(t_ray *ray, t_shapes *shape, t_vect *pos, t_vect *nrm);

//RAY_UTILS.C
unsigned int	dec2hex(int n);
void			pixel_colors(t_data data, t_ray *ray);
void			pixel_colors_shadow(t_data data, t_ray *ray);
int				init_ray(t_ray *ray);
void			free_ray(t_ray *ray);

#endif



