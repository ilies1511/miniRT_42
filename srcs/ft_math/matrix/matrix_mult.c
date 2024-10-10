/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:55 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 14:51:37 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

static inline double	kahan_sum_inline(double *nbs, size_t count)
{
	size_t	i;
	double	sum;
	double	next_add;
	double	compensation;
	double	total;

	i = 0;
	sum = 0.0;
	compensation = 0.0;
	total = 0.0;
	while (i < count)
	{
		next_add = nbs[i] - compensation;
		total = sum + next_add;
		compensation = (total - sum) - next_add;
		sum = total;
		i++;
	}
	return (sum);
}

#ifndef NDBUG

// using kahan sum to reduce floating point addition errors
t_tuple	mtx_mult_mt(t_matrix m, t_tuple tup)
{
	t_tuple	res;
	double	tmp[4];
	int		i;
	int		j;

	ft_bzero(&res, sizeof(res));
	rt_assert(m.type == MAT4X4, __FILE__, __LINE__,
		"mult_mt: given matrix is not 4x4");
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp[j] = m.m[i][j] * tup.arr[j];
			j++;
		}
		res.arr[i] = kahan_sum_inline(tmp, 4);
		i++;
	}
	return (res);
}

#else
// using kahan sum to reduce floating point addition errors
t_tuple	mtx_mult_mt(t_matrix m, t_tuple tup)
{
	t_tuple									res;
	double __attribute__	((aligned(16)))	tmp[4];
	uint8_t									j;
	uint8_t									i;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp[j] = m.m[i][j] * tup.arr[j];
			j++;
		}
		res.arr[i] = kahan_sum_inline(tmp, 4);
		i++;
	}
	return (res);
}

#endif //n NDBUG

t_matrix	mtx_mult_mm(t_matrix ma, t_matrix mb)
{
	t_matrix	ret;
	int			i;
	int			j;
	int			k;
	double		tmp[4];

	rt_assert(ma.type == MAT4X4 && mb.type == MAT4X4, __FILE__, __LINE__,
		"Error: matrix multiplication_mm of wrong matrix type");
	ret.type = MAT4X4;
	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				tmp[k] = ma.m[i][k] * mb.m[k][j];
				k++;
			}
			ret.m[i][j++] = kahan_sum_inline(tmp, 4);
		}
	}
	return (ret);
}
