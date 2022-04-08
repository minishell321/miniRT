/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:06:33 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 15:10:28 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size;
	int		height;
	int		width;
}	t_data;

typedef	struct	s_shape {
	char	*type;
	double	coordinates[3];
	double	diameter;
	int		color[3];
}	t_shape;



typedef struct	s_node {
	int	x;
	int	y;
	int	z;
} 	t_node;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_shape	*shape;
}	t_vars;

// MLX_UTILS.C
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// UTILS.C
void	ft_error(void);

// PARSING_UTILS.C
double	ft_atof(char *str);

#endif
