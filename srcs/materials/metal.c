/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:45 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:09:56 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <ft_material.h>

t_material	eng_new_material_polished_metal(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.05;
	mat.diffuse = 0.1;
	mat.specular = 0.9;
	mat.shininess = 300;
	mat.reflective = 0.3;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	mat.bump = NULL;
	return (mat);
}

t_material	material_silver_and_gold(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.fcolor = new_fcolor(1, 0.843, 0, 1);
	mat.pattern = pat_stripe_pattern(new_fcolor(1, 1, 1, 1), \
		new_fcolor(1, 0.843, 0, 1));
	mat.pattern = NULL;
	mat.ambient = 0.05;
	mat.diffuse = 0.1;
	mat.specular = 0.9;
	mat.shininess = 300;
	mat.reflective = 0.9;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	mat.bump = NULL;
	return (mat);
}
