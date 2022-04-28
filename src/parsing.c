/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:43:23 by rburri            #+#    #+#             */
/*   Updated: 2022/04/28 10:05:54 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	check_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		if (ft_isdigit(s[i]) || s[i] == ' ' || s[i] == '.' || \
		s[i] == ',' || s[i] == '-')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	check_param(char **split)
{
	int	i;

	i = 1;
	while (split[i])
	{
		if (check_char(split[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_split(char **split)
{
	if (ft_strncmp(split[0], "A", 2) == 0 || ft_strncmp(split[0], "C", 2) == 0)
	{
		if (check_param(split))
			return (1);
	}
	else if (ft_strncmp(split[0], "L", 2) == 0 || \
	ft_strncmp(split[0], "sp", 3) == 0)
	{
		if (check_param(split))
			return (1);
	}
	else if (ft_strncmp(split[0], "pl", 3) == 0 || \
	ft_strncmp(split[0], "cy", 3) == 0)
	{
		if (check_param(split))
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	parse_line(char *str, t_scene *scene)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split((str + i), ' ');
	if (ft_strncmp(split[0], "\n", 1) == 0)
	{
		ft_free_split(split);
		return (0);
	}
	if (check_split(split))
	{
		ft_free_split(split);
		return (1);
	}
	else
	{
		if (upload_scene(split, scene))
		{
			free_scene_el(scene);
			return (1);
		}
	}
	ft_free_split(split);
	return (0);
}

int	read_file(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_line(line, scene))
		{
			free(line);
			ft_error();
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	print_scene(scene);
	return (0);
}
