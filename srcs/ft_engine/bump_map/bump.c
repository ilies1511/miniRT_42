/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:39 by iziane            #+#    #+#             */
/*   Updated: 2024/10/10 15:07:39 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <libft.h>
#include <main.h>
#include <ft_bump_map.h>

t_bump	*bump_new_bump(void)
{
	t_bump		*bump;

	bump = ft_malloc(sizeof(t_bump));
	if (!bump)
		ft_error("Malloc failed", __FILE__, __LINE__, 1);
	bump->base_obj = eng_new_obj();
	bump->base_obj.type = OBJ_BUMP;
	bump->type = BUMP_DEFAULT;
	return (bump);
}

t_vec	bump_normal_at(t_obj obj, t_bump bump_map, \
		t_point world_point, t_vec normal_base)
{
	t_point	obj_point;
	t_point	bump_point;

	obj_point = mtx_mult_mt(obj.inverse, world_point);
	bump_point = mtx_mult_mt(bump_map.base_obj.inverse, obj_point);
	if (bump_map.type == BUMP_DEFAULT)
		return (ft_assert(0, __FILE__, __LINE__, "bump type not specified"), \
			new_vec(0, 0, 0));
	if (bump_map.type == BUMP_WAVE)
		return (bump_wave_normal_at(bump_map, bump_point, normal_base));
	ft_assert(0, __FILE__, __LINE__, "pat_color_at: invalid pattern type");
	__builtin_unreachable();
}
