/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:48 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:31:49 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <ft_material.h>

t_material	eng_blue_sky(void)
{
	t_material	mat;

	mat.fcolor.r = 4.0 / 255;
	mat.fcolor.g = 100.0 / 255;
	mat.fcolor.b = 280.0 / 255;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 1.3;
	mat.diffuse = 1;
	mat.specular = 0;
	mat.shininess = 0;
	mat.reflective = 0;
	mat.transparency = 0;
	mat.refractive_index = 1.000;
	mat.bump = NULL;
	return (mat);
}

t_material	eng_water(void)
{
	t_material	mat;

	mat.fcolor.r = 0.2;
	mat.fcolor.g = 0.5;
	mat.fcolor.b = 0.7;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.bump = bump_wave();
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 400;
	mat.reflective = 0.5;
	mat.transparency = 0.4;
	mat.refractive_index = 1.333;
	return (mat);
}

t_material	eng_sand(void)
{
	t_material	mat;

	mat.fcolor.r = 0.76;
	mat.fcolor.g = 0.7;
	mat.fcolor.b = 0.5;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.bump = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.7;
	mat.specular = 0.1;
	mat.shininess = 10;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1.00029;

	mat.bump = NULL;
	return (mat);
}
