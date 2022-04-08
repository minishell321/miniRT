/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 18:09:59 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "basic_struct.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
// printf perror strerror
# include <stdlib.h>
// malloc free
# include <fcntl.h>
//open
# include <unistd.h>
// close read write


// MLX_UTILS.C
void	my_mlx_pixel_put(t_data *data, double x, int y, int color);

// UTILS.C
void	ft_error(void);
int		my_close(int keycode, t_vars *vars);

// PARSING_UTILS.C
double	ft_atof(char *str);

// PARSING.C
void	read_file(t_scene *scene, char *file);

// UPLOAD_SCENE.C
int		upload_scene(char **split, t_scene *scene);

#endif
