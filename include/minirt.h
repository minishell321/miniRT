/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/05/03 11:31:54 by vbotev           ###   ########.fr       */
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

// int 	parse_scene(t_shape *shape, char *file);
// MLX_UTILS.C
void			my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);

// UTILS.C
unsigned int	encode_rgb(unsigned char r, unsigned char g, unsigned char b);
void			ft_error(void);
int				my_close(int keycode, t_data *data);
int				close_win(t_data *data);
void			init_data(t_data *data, t_scene *scene);

// PARSING_UTILS.C
int				init_vect_3d(t_shapes *shape, char *str);
int				init_colors(t_shapes *shape, char *str);
int				init_coord(t_shapes *shape, char *str);
void			insert_shape_at_end(t_scene *scene, t_shapes *shape);
int				ft_isspace_nnl(int c);
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
// CREATE_SHAPE.C
int				create_shape(char **split, t_scene *scene);
// VECTOR_UTILS.C
double	norm_squared(double *crdnt);
double	*normalize(double *crdnt);
double	dot_product(double *a, double *b);
double  *vec_add(double *a, double *b, double *res);
double  *vec_sub(double *a, double *b, double *res);
// VECTOR_UTILS2.C
double	*vec_scalar_multip(double scalar, double *vec, double *res);
double	*vec_dup(double *vec, double *dup);
double	*vec_assign(double *vec, double x, double y, double z);
double	*vec_mat_multip(double **matrix, double *vec, double *res);
double	*vec_cross_prod(double *a, double *b, double *res);
// TRACING.C
double  intersection(t_ray *ray, t_shapes *shape, double *pos, double *nrm);
double *dir_vec(double *ray_dir, int i, int j, t_data data);
int scene_intersect(t_data data, t_ray *ray);
int ray_tracing(t_data data);
//RAY_UTILS.C
unsigned int	dec2hex(int n);
void			pixel_colors(t_data data, t_ray *ray);
int				init_ray(t_ray *ray);
void			free_ray(t_ray *ray);
//GEO_TRANSFORM
t_geo_tfrm	*geo_transform(double *trans, double *rot, double *scale, t_geo_tfrm *tfrm);
//MATRIX_UTILS.C
double	**init_mtrx(double **matrix);
int	matrix_multiply(double **a, double **b, double **res);
double	matrix_det(double matrix[4][4], int order);
double	**matrix_inv(double a[4][4], double f);
double	**transpose(double a[4][4], double fac[4][4], double r);
double	**inverse(double **matrix);

#endif



