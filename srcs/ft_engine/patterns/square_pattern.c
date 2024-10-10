/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_pattern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:11 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 14:54:12 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_patterns.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>

t_pattern	*pat_square3d_pattern(t_fcolor color1, t_fcolor color2)
{
	t_pattern	*pattern;

	pattern = pat_new_pattern();
	pattern->type = PAT_SQUARE_3D;
	gc_dyn_arr_add_save((void **)&pattern->colors, &color1, 0);
	gc_dyn_arr_add_save((void **)&pattern->colors, &color2, 1);
	pattern->color_count = 2;
	return (pattern);
}

t_fcolor	pat_square3d_at(t_pattern pat, t_point point)
{
	return (pat.colors[(int)fmod(fabs(point.x) + fabs(point.y)
				+ fabs(point.z), 2)]);
}
