/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:33:12 by rburri            #+#    #+#             */
/*   Updated: 2022/05/13 14:03:03 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_STRUCT_H
# define BASIC_STRUCT_H

# define M_PI 3.141592653589793

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}	t_vect;

typedef struct s_3vect
{
	t_vect	u;
	t_vect	v;
	t_vect	tmp;
}	t_3vect;

typedef struct s_specular
{
	t_vect	rfl;
	float	s;
}	t_specular;

typedef struct s_shapes
{
	int				type;
	t_vect			coordinates;
	t_vect			v_3d;
	float			diam;
	float			h;
	unsigned char	colors[3];
	int				color;
	struct s_shapes	*next;
}	t_shapes;

typedef struct s_ray
{
	t_vect			org;
	t_vect			dir;
	t_vect			pos;
	t_vect			nrm;
	unsigned char	sf_color[3];
	float			intr;
}	t_ray;

typedef struct s_amb
{
	float			light;
	unsigned char	colors[3];
	int				color;
}	t_amb;

typedef struct s_light
{
	t_vect	coordinates;
	float	ratio;
}	t_light;

typedef struct s_camera
{
	t_vect	coordinates;
	t_vect	v_3d;
	float	fov;
}	t_camera;

typedef struct s_scene
{
	t_shapes	*stack;
	t_amb		*amb;
	t_light		*light;
	t_camera	*camera;
	float		pixel_intensity;
}	t_scene;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size;
	int		h;
	int		w;
	void	*mlx;
	void	*win;
	t_scene	*s;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

#endif
