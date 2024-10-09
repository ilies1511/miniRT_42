/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:35 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:36 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <ft_colors.h>

t_fcolor	mult_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	new_color;

	new_color.r = a.r * b.r;
	new_color.g = a.g * b.g;
	new_color.b = a.b * b.b;
	new_color.a = 1.0;
	return (new_color);
}

t_fcolor	eng_mult_color_f(t_fcolor color1, double scale)
{
	t_fcolor	result;

	result.r = color1.r * scale;
	result.g = color1.g * scale;
	result.b = color1.b * scale;
	result.a = color1.a * scale;
	return (result);
}

t_fcolor	eng_add_color_color(t_fcolor color1, t_fcolor color2)
{
	t_fcolor	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	result.a = color1.a + color2.a;
	return (result);
}

t_fcolor	eng_mult_color_color(t_fcolor color1, t_fcolor color2)
{
	t_fcolor	result;

	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	result.a = color1.a * color2.a;
	return (result);
}
