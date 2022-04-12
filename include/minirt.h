/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/04/12 09:40:53 by rburri           ###   ########.fr       */
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


int 	parse_scene(t_shape *shape, char *file);
// MLX_UTILS.C
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);

// UTILS.C
void	ft_error(void);
int		my_close(int keycode, t_vars *vars);

// PARSING_UTILS.C
int	    init_vect_orient_3d(t_shapes *shape, char *str);
int	    init_colors(t_shapes *shape, char *str);
int	    init_coord(t_shapes *shape, char *str);
void	insert_shape_at_end(t_scene *scene, t_shapes *shape);
int		ft_isspace_nnl(int c);
// SCENE_UTILS.C
void	init_scene(t_scene *scene);
void	print_scene(t_scene *scene);
void	free_scene_el(t_scene *scene);

// FT_ATOF.C
double	ft_atof(char *str);

// PARSING.C
int	read_file(t_scene *scene, char *file);

// UPLOAD_SCENE.C
int		upload_scene(char **split, t_scene *scene);
// CREATE_SHAPE.C
int     create_shape(char **split, t_scene *scene);

#endif
