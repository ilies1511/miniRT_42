/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple3_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:21 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:22 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

#ifndef NDBUG

double	len_v(t_vec v)
{
	rt_assert(is_vec(v), __FILE__, __LINE__, "getting length of a none vector");
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_vec	norm(t_vec v)
{
	double	len;

	len = len_v(v);
	rt_assert(!eq_f(len, 0.0), __FILE__, __LINE__,
		"normalizing a vec with len 0");
	return (div_v(v, len));
}

double	dot_prod(t_vec a, t_vec b)
{
	rt_assert(is_vec(a) && is_vec(b), __FILE__, __LINE__,
		"getting dot product of a none vector");
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w
	);
}

t_vec	cross_prod(t_vec a, t_vec b)
{
	rt_assert(is_vec(a) && is_vec(b), __FILE__, __LINE__,
		"getting corss product of a none vector");
	return (new_vec(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
#endif //n NDBUG
