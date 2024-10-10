/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple2_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:25 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:26 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

#ifndef NDBUG

t_tuple	add_t(t_tuple a, t_tuple b)
{
	t_tuple	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	sum.w = a.w + b.w;
	if (sum.w - (EPSILON) > 1.0)
		rt_assert(0, __FILE__, __LINE__, "add_t: w off");
	if (sum.w + (EPSILON) < 0.0)
		rt_assert(0, __FILE__, __LINE__, "add_t: w off");
	return (sum);
}

t_tuple	sub_t(t_tuple a, t_tuple b)
{
	t_tuple	dif;

	dif.x = a.x - b.x;
	dif.y = a.y - b.y;
	dif.z = a.z - b.z;
	dif.w = a.w - b.w;
	rt_assert(greater_eq_f(dif.w, 0.0), __FILE__, __LINE__,
		"dif of 2 tuples is < 0.0, subtracted a point from a vector?");
	if (dif.w - (EPSILON) > 1.0)
		rt_assert(0, __FILE__, __LINE__, "sub_t: w off");
	if (dif.w + (EPSILON) < 0.0)
		rt_assert(0, __FILE__, __LINE__, "sub_t: w off");
	return (dif);
}

/*
	Negating Tuples (Vorzeichenwechsel)
*/
t_vec	negate_v(t_vec v)
{
	t_vec	neg;
	t_tuple	dif;

	if (v.w - (EPSILON) > 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	if (v.w + (EPSILON) < 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	rt_assert(is_vec(v), __FILE__, __LINE__, "negating a none vector");
	neg.x = -v.x;
	neg.y = -v.y;
	neg.z = -v.z;
	neg.w = v.w;
	dif = add_t(v, neg);
	rt_assert(eq_f(dif.x, 0.0) && eq_f(dif.y, 0.0) && eq_f(dif.z, 0.0),
		__FILE__, __LINE__,
		"negation + base != 0, maybe a zero devison somewhere leading to INF?");
	return (neg);
}

/*
	Scenario: tuple * scalar
*/
t_vec	mult_v(t_vec v, double scalar)
{
	t_vec	prod;

	rt_assert(is_vec(v), __FILE__, __LINE__, "multiplying a none vector");
	prod.x = v.x * scalar;
	prod.y = v.y * scalar;
	prod.z = v.z * scalar;
	prod.w = v.w * scalar;
	rt_assert(scalar != INFINITY, __FILE__, __LINE__, "multiplied by infinity");
	if (prod.w - (EPSILON) > 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	if (prod.w + (EPSILON) < 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	return (prod);
}

/*
	Dividing a tuple by a scalar
*/
t_vec	div_v(t_vec v, double scalar)
{
	t_vec	quot;

	rt_assert(!eq_f(scalar, 0.0), __FILE__, __LINE__, "zero devision");
	rt_assert(is_vec(v), __FILE__, __LINE__, "deviding a none vector");
	quot.x = v.x / scalar;
	quot.y = v.y / scalar;
	quot.z = v.z / scalar;
	quot.w = v.w / scalar;
	if (quot.w - (EPSILON) > 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	if (quot.w + (EPSILON) < 0.0)
		rt_assert(0, __FILE__, __LINE__, "w off");
	return (quot);
}
#endif //n NDBUG
