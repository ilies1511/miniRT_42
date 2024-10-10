/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:57 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:57:33 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <stdlib.h>

t_world	eng_default_world(void)
{
	t_world		def;
	t_light		light;
	t_sphere	sph;

	def = eng_new_world();
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(-10, 10, -10));
	eng_add_obj_to_world(&def, (t_obj_ptr) & light);
	sph = eng_new_sphere();
	sph.base_obj.material.fcolor = new_fcolor(0.8, 1.0, 0.6, 1);
	sph.base_obj.material.diffuse = 0.7;
	sph.base_obj.material.specular = 0.2;
	eng_add_obj_to_world(&def, (t_obj_ptr) & sph);
	sph = eng_new_sphere();
	eng_set_transform((t_obj_ptr) & sph, mtx_scale(0.5, 0.5, 0.5));
	eng_add_obj_to_world(&def, (t_obj_ptr) & sph);
	return (def);
}
