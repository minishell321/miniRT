/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:33:12 by rburri            #+#    #+#             */
/*   Updated: 2022/04/12 10:31:25 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_STRUCT_H
# define BASIC_STRUCT_H

# define M_PI 3.141592653589793

typedef struct s_shapes
{
	char	*type;
	double	coordinates[3];
	double	vect_orient_3d[3];
	double	diameter;
	double	height;
	int		colors[3];
	struct s_shapes *next;
}	t_shapes;

typedef	struct	s_shape {
	char	*type;
	double	coordinates[3];
	double	diameter;
	int		colors[3];
}	t_shape;

typedef struct s_amb_light
{
	double	light;
	int		colors[3];
}	t_amb_light;

typedef struct s_light
{
	double	coordinates[3];
	double	ratio;
}	t_light;

typedef struct s_camera
{
	double	coordinates[3];
	double	vect_orient_3d[3];
	int		fov;
}	t_camera;

typedef struct s_scene
{
	t_shapes	*stack;
	t_amb_light	*amb_light;
	t_light		*light;
	t_camera	*camera;
}	t_scene;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size;
	int		height;
	int		width;
	void	*mlx;
	void	*win;
	t_scene	*scene;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

#endif
