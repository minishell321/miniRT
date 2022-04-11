/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:43:23 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 08:42:39 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	check_param(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) || s[i] == ' ' || s[i] == '.' || s[i] == ',')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	check_split(char **split)
{
	int	i;

	i = 1;
	if (ft_strncmp(split[0], "A", 2) || ft_strncmp(split[0], "C", 2) \
		|| ft_strncmp(split[0], "L", 2) || ft_strncmp(split[0], "sp", 3) \
		|| ft_strncmp(split[0], "pl", 3) || ft_strncmp(split[0], "cy", 3))
		return (1);
	while (split[i])
	{
		if (check_param(split[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	parse_line(char *str, t_scene *scene)
{
	int		i;
	char	**split;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			split = ft_split((str + i), ' ');
			if (check_split(split))
				continue;
			else
				upload_scene(split, scene);
		}
		i++;
	}
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
	free(line);
	close(fd);
	return (0);
}

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
				shape->colors[k++] = ft_atoi(tmp);
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

