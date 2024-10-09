/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:43 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:44 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>

t_material	eng_new_material(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1;
	mat.bump = NULL;
	return (mat);
}
