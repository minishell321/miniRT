/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 16:34:37 by rburri           ###   ########.fr       */
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

#endif
