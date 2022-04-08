/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:33:12 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 16:44:41 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_STRUCT_H
# define BASIC_STRUCT_H

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
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_shape	*shape;
}	t_vars;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_coord {
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_shape
{
	char	*type;
	t_coord	*coord;
	t_coord	*vect_orient_3d;
	double	diameter;
	double	height;
	t_rgb	*color;
}	t_shape;

typedef struct s_amb_light
{
	double	light;
	t_rgb	color;
}	t_amb_light;

typedef struct s_lignt
{
	t_coord	*coord;
	double	ratio;
}	t_light;

typedef struct s_camera
{
	t_coord	*coord;
	t_coord	*vect_orient_3d;
	int		fov;
}	t_camera;

typedef struct s_scene
{
	t_shape		*stack;
	t_amb_light	*amb_light;
	t_light		*light;
	t_camera	*camera;
}	t_scene;

#endif

// typedef struct s_cylinder
// {
// 	t_coord *coord;
// 	t_coord *vect_orient_3d;
// 	double	diameter;
// 	double	height;
// 	t_rgb	*color;
// }				t_cylinder;

// typedef struct s_plan
// {
// 	t_coord *coord;
// 	t_coord *vect_orient_3d;
// 	t_rgb	*color;
// }				t_plan;