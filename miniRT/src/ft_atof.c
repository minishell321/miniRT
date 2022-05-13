/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 08:14:57 by rburri            #+#    #+#             */
/*   Updated: 2022/04/11 11:57:44 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	int_len(int num)
{
	int	i;

	i = 0;
	if (num < 0)
		num *= -1;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static void	check_sign(char *str, int *factor, int *i)
{
	int	j;

	j = 0;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			*factor = -1;
		*i += 1;
	}
}

double	ft_atof(char *str)
{
	double	fractional;
	int		atoi;
	int		i;
	int		factor;

	factor = 1;
	fractional = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	check_sign(str + i, &factor, &i);
	atoi = ft_atoi(str);
	i += int_len(atoi);
	if (str[i] != '.')
		return (atoi);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		factor *= 10;
		fractional = fractional * 10 + str[i] - 48;
		i++;
	}
	fractional /= factor;
	return (atoi + fractional);
}
