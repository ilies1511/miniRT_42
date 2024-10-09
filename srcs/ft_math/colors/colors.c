/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:33 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:34 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_floats.h>
#include <ft_colors.h>

t_fcolor	add_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	sum;

	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	sum.a = 1.0;
	return (sum);
}

/*
	Subtraction of two tuples
*/
t_fcolor	sub_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	dif;

	dif.r = a.r - b.r;
	dif.g = a.g - b.g;
	dif.b = a.b - b.b;
	dif.a = 1.0;
	return (dif);
}

t_fcolor	scale_fcolor(t_fcolor c, double scalar)
{
	t_fcolor	res;

	res.r = c.r * scalar;
	res.g = c.g * scalar;
	res.b = c.b * scalar;
	res.a = 1.0;
	return (res);
}

t_fcolor	div_fcolor(t_fcolor c, double div)
{
	t_fcolor	res;

	res.r = c.r / div;
	res.g = c.g / div;
	res.b = c.b / div;
	res.a = 1.0;
	return (res);
}

bool	eq_fcolor(t_fcolor a, t_fcolor b)
{
	return (eq_f(a.r, b.r) && eq_f(a.g, b.g)
		&& eq_f(a.b, b.b) && eq_f(a.a, b.a));
}
