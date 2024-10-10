/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:55:20 by iziane            #+#    #+#             */
/*   Updated: 2024/10/10 14:55:42 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

t_fcolor	eng_shade_hit(t_world world, t_computation comp, \
	size_t remaining_reflects)
{
	t_shade_hit_norm	n;

	n.color = fcolor_black();
	n.i = -1;
	while (++n.i < (int)world.light_count)
	{
		n.light = adjust_light(world.lights[n.i]);
		if (!in_light_fov(n.light, comp.point))
			n.in_shadow = true;
		else
			n.in_shadow = eng_is_shadowed(world, comp.over_point, n.light);
		n.surface = eng_lighting(comp, n.light, n.in_shadow);
		n.reflected = ref_reflected_color(world, comp, remaining_reflects);
		n.refracted = refracted_color(world, comp, remaining_reflects);
		if (comp.obj->material.reflective > 0 \
				&& comp.obj->material.transparency > 0)
		{
			n.reflactance = ref_schlick(comp);
			n.reflected = scale_fcolor(n.reflected, n.reflactance);
			n.refracted = scale_fcolor(n.refracted, 1.0 - n.reflactance);
		}
		calculate_color(&n);
	}
	return (n.color);
}
