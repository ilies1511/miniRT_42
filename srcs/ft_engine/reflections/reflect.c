/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:42 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:36:40 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <ft_reflection.h>

t_vec	ref_reflect(t_vec vec, t_vec surface_normal)
{
	double	dot;
	t_vec	scaled_normal;

	dot = dot_prod(vec, surface_normal);
	scaled_normal = mult_v(surface_normal, 2 * dot);
	return (sub_t(vec, scaled_normal));
}

t_fcolor	ref_reflected_color(t_world world, t_computation comp,
		size_t remaining_reflects)
{
	t_ray		reflected_ray;
	t_fcolor	color;

	if (eq_f(comp.obj->material.reflective, 0) || !remaining_reflects)
		return (fcolor_black());
	reflected_ray = eng_new_ray(comp.over_point, comp.reflection);
	color = eng_color_at(world, reflected_ray, remaining_reflects - 1);
	return (scale_fcolor(color, comp.obj->material.reflective));
}
