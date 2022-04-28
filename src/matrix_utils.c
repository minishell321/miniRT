/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:20:56 by vbotev            #+#    #+#             */
/*   Updated: 2022/04/28 14:35:13 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double **init_mtrx(double **matrix)
{
    int     i;
    int     j;

    matrix = malloc(sizeof(double *) * 4);
  //  if (matrix == 0)
  //      return (1);
    i = 0;
    while (i < 4)
    {
        matrix[i] = malloc(sizeof(double) * 4);
      //  if (matrix[i] == 0)
        //    return (1);
        j = 0;
        while (j < 4)
        {
            if (j == i)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
            j++;
        }
        i++;
    }
	printf("matrix[0][0] = %f\n", matrix[0][0]);
    return (matrix);
}

int matrix_multiply(double **a, double **b, double **res)
{
    int     i;
    int     j;
    int     k;
    double  sum;

    sum = 0;
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            k = 0;
            while (k < 4)
            {
                sum += a[i][k] * b[k][j];
                k++;
            }
            res[i][j] = sum;
            sum = 0;
            j++;
        }
        i++;
    }
    return(0);
}

double  matrix_det(double matrix[4][4], int order)
{
    double  s;
    double  det;
    double  tmp[4][4];
    int     i[5];

	det = 0;
	s = 1;
	if (order == 1)
		return (matrix[0][0]);
	else
	{
	det = 0;
    i[4] = -1;
    while (++i[4] < order)
    {
        i[2] = 0;
        i[3] = 0;
        i[0] = -1;
        while(++i[0] < order)
        {
            i[1] = -1;
            while (++i[1] < order)
            {
                tmp[i[0]][i[1]] = 0;
                if (i[0] != 0 && i[1] != i[4])
                {
                    tmp[i[2]][i[3]] = matrix[i[0]][i[1]];
                    if (i[3] < (order - 2))
                        i[3]++;
                    else
                    {
                        i[3] = 0;
                        i[2]++;
                    }
                }
            }
        }
		det = det + s * (matrix[0][i[4]] * matrix_det(tmp, order - 1));
		s = -1 * s;
    }
	}
    return (det);
}

double	**matrix_inv(double a[4][4], double f)
{
    double  b[4][4];
    double  fac[4][4];
    int     i[6];

    i[1] = -1;
    while (++i[1] < f)
    {
        i[0] = -1;
        while (++i[0] < f)
        {
            i[2] = 0;
            i[3] = 0;
            i[4] = -1;
            while(++i[4] < f)
            {
                i[5] = -1;
                while (++i[5] < f)
                {
                    if (i[4] != i[1] && i[5] != i[0])
                    {
                        b[i[2]][i[3]] = a[i[4]][i[5]];
                        if (i[3] < (f - 2))
                            i[3]++;
                        else
                        {
                            i[3] = 0;
                            i[2]++;
                        }
                    }
                }
            }
            fac[i[1]][i[0]] = pow(-1, i[1] + i[0]) * matrix_det(b, f - 1);
        }
    }
    return (transpose(a, fac, f));
}

double  **transpose(double a[4][4], double fac[4][4], double r)
{
    int i[2];
    double  b[4][4];
    double  **inv;
    double  d;

	inv = NULL;
    inv = init_mtrx(inv);
    i[0] = -1;
    while (++i[0] < r)
    {
        i[1] = -1;
        while (++i[1] < r)
            b[i[0]][i[1]] = fac[i[1]][i[0]];
    }
    d = matrix_det(a, r);
	printf("d = %f\n", d);
    i[0] = -1;
    while (++i[0] < r)
    {
        i[1] = -1;
        while (++i[1] < r)
		{
            inv[i[0]][i[1]] = b[i[0]][i[1]] / d;
		}
    }
    return (inv);
}

double [][4]ptr2arr(double **matrix)
{
	double	ret[4][4];
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret[i][j] = matrix[i][j];
	}
	return (ret);
}
