/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe_pattern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:08 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:36:09 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_patterns.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>

t_pattern	*pat_stripe_pattern(t_fcolor color1, t_fcolor color2)
{
	t_pattern	*pattern;

	pattern = pat_new_pattern();
	pattern->type = PAT_STRIPE;
	gc_dyn_arr_add_save((void **)&pattern->colors, &color1, 0);
	gc_dyn_arr_add_save((void **)&pattern->colors, &color2, 1);
	pattern->color_count = 2;
	return (pattern);
}

t_fcolor	pat_stripe_at(t_pattern pat, t_point point)
{
	if (fmod(floor(point.x), 2) == 0)
		return (pat.colors[0]);
	return (pat.colors[1]);
}