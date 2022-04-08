/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:43:23 by rburri            #+#    #+#             */
/*   Updated: 2022/04/08 15:43:54 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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