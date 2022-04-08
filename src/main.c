/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:05:09 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 13:56:30 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	my_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->shape);
		exit(0);
	}
	return (0);
}

double norm_squared(double *crdnt)
{
	double	res;

	res = crdnt[0] * crdnt[0] + crdnt[1] * crdnt[1] + crdnt[2] * crdnt[2];
	return(res);
}

double	*normalize(double *crdnt)
{
	double	norm;

	norm = sqrt(norm_squared(crdnt));
	crdnt[0] = crdnt[0] / norm;
	crdnt[1] = crdnt[1] / norm;
	crdnt[2] = crdnt[2] / norm;
	return (crdnt);
}

double	dot_product(double *a, double *b)
{
	double	result;

	result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return (result);
}

// ASSUMING AN ORIGIN OF THE RAY AT {0, 0, 0}
int	intersection(double *ray_dir, double *sphere, double sp_diameter)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	dist_to_sphere_center[3];

	// using {0,0,0} as origin otherwise this would have to be modified
	dist_to_sphere_center[0] = -1 * sphere[0];
	dist_to_sphere_center[1] = -1 * sphere[1];
	dist_to_sphere_center[2] = -1 * sphere[2];
	a = 1;
	b = 2 * dot_product(ray_dir, dist_to_sphere_center);
	c = norm_squared(dist_to_sphere_center) - (sp_diameter * sp_diameter);
	delta = b * b - (4 * a * c);
	if (delta < 0)
		return (0);
	else if ((-b + sqrt(delta)) / (2 * a) > 0)
		return (1);
	else
		return (0);

}

double *dir_vec(double *ray_dir, int i, int j, int W, int H, double fov)
{
	ray_dir[0] = j - W / 2;
	ray_dir[1] = i - H / 2;
	ray_dir[2] = -W / (2 * tan (fov / 2));
	return (ray_dir);
}

// FOV SET TO 60 degrees
int	ray_tracing(t_data img, t_shape *shape)
{
	int		i;
	int		j;
	double	fov;
	double	*ray_dir;

	i = 0;
	fov = 60 * 3.1415926535897 / 180;
	ray_dir = malloc(sizeof(double) * 3);
	if (ray_dir == 0)
		return (1);
	while (i < img.height)
	{
		j = 0;
		while (j < img.width)
		{
			if (intersection(normalize(dir_vec(ray_dir, i, j, img.width, img.height, fov)), shape->coordinates, shape->diameter))
				my_mlx_pixel_put(&img, i, j, 0xf5aa42);
			j++;
		}
		i++;
	}
	free(ray_dir);
	return (0);
}


// NOT FINISHED

int	parse_scene(t_shape *shape, char *file)
{
	int		fd;
	int		i;
	int		j;
	int		k;
	int		flag;
	char	*str;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	str = get_next_line(fd);
	j = 0;
	k = 0;
	flag = 0;
	while (str != 0)
	{
		i = 0;
		while (str[i] != 0)
		{
			if (str[i] == ' ')
				i++;
			else if (str[i] > 96 && str[i] < 123 && flag == 0)
			{
				while (str[i + j] != ' ')
					j++;
				shape->type = ft_substr(str, i, j);
				i += j + 1;
				j = 0;
				flag = 1;
			//	printf("Here\n");
			}
			else if ((ft_isdigit(str[i]) || (str[i] > 42 && str[i] < 47)) && flag == 1)
			{
				while (str[i + j] != ',' && str[i + j] != ' ')
					j++;
				tmp = ft_substr(str, i, j);
				shape->coordinates[k++] = ft_atoi(tmp);
				free(tmp);
				i += j + 1;
				j = 0;
				if (k == 3)
				{
					flag = 2;
					k = 0;
				}
			}
			else if (ft_isdigit(str[i]) && flag == 2)
			{
				while (str[i + j] != ' ')
					j++;
				tmp = ft_substr(str, i, j);
				shape->diameter = ft_atoi(tmp);
				free(tmp);
				i += j + 1;
				flag = 3;
				j = 0;
			}
			else if ((ft_isdigit(str[i]) || (str[i] > 42 && str[i] < 47)) && flag == 3)
			{
				while (str[i + j] != ',' && str[i + j] != ' ' && str[i + j] != 0)
					j++;
				tmp = ft_substr(str, i, j);
				shape->color[k++] = ft_atoi(tmp);
				free(tmp);
				i += j + 1;
				j = 0;
				if (k == 3)
					flag = 4;
			}
		}
		str = get_next_line(fd);
	}
	close (fd);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	img;
	t_vars	vars;
	t_shape	*shape;
	

	if (argc == 2)
	{
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 1024, 1024, "miniRT");
		img.img = mlx_new_image(vars.mlx, 1024, 1024);
		(void)argv;
		shape = malloc(sizeof(t_shape));
		if (shape == 0)
			return (1);
		if (parse_scene(shape, argv[1]))
			ft_error();
		img.height = 1024;
		img.width = 1024;
		printf("shape->type = %s\n", shape->type);
		printf("shape->coordinates[0] = %f\n", shape->coordinates[0]);
		printf("shape->coordinates[1] = %f\n", shape->coordinates[1]);
		printf("shape->coordinates[2] = %f\n", shape->coordinates[2]);
		printf("shape->diameter = %f\n", shape->diameter);
		vars.shape = shape;

		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		if (ray_tracing(img, shape))
			ft_error();
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_hook(vars.win, 2, 1L << 0, my_close, &vars);
		mlx_loop(vars.mlx);
	}
	else
		ft_error();
	return (0);
}
