/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:52:14 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 18:09:08 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	create_amb_light(char **split, t_scene *scene)
{
	return (0);
}

static int	create_camera(char **split, t_scene *scene)
{
	return (0);
}

static int	create_light(char **split, t_scene *scene)
{
	return (0);
}

static int	create_shape(char **split, t_scene *scene)
{
	return (0);
}

int	upload_scene(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "A", 2))
		if (create_amb_light(split, scene))
			return (1);
	else if (!ft_strncmp(split[0], "C", 2))
		if (create_camera(split, scene))
			return (1);
	else if (!ft_strncmp(split[0], "L", 2))
		if (create_light(split, scene))
			return (1);
	else
		if (create_shape(split, scene))
			return (1);
	return (0);
}
