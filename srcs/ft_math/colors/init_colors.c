/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:30 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:31 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_floats.h>
#include <ft_colors.h>

t_fcolor	new_fcolor(double r, double g, double b, double a)
{
	t_fcolor	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 1;
	(void)a;
	return (color);
}

t_fcolor	fcolor_black(void)
{
	return (new_fcolor(0, 0, 0, 1));
}

t_fcolor	fcolor_white(void)
{
	return (new_fcolor(1, 1, 1, 1));
}

t_uintcolor	fcolor_to_uintcolor(t_fcolor fcolor)
{
	t_uintcolor	ret;

	ret.argb.r = (uint8_t)(0xFF * clamp_f(fcolor.r, 0, 1));
	ret.argb.g = (uint8_t)(0xFF * clamp_f(fcolor.g, 0, 1));
	ret.argb.b = (uint8_t)(0xFF * clamp_f(fcolor.b, 0, 1));
	ret.argb.a = 0xFF;
	return (ret);
}

void	print_fcolor(char *str, t_fcolor col)
{
	printf("%sr:%f; g: %f; b: %f; a: %f\n", str, col.r, col.g, col.b, col.a);
}
