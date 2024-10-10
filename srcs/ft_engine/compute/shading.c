/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:37:14 by iziane            #+#    #+#             */
/*   Updated: 2024/10/10 14:55:29 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

//t_light	adjust_light(t_light in)
//{
//	t_light	out;
//	t_vec	offset;
//
//	out = in;
//	offset = norm(new_vec(1, 0, 0));
//	offset = mtx_mult_mt(mtx_rotation_y(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_rotation_z(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_rotation_x(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_scale(in.radius, in.radius, in.radius), offset);
//	out.origin = add_t(out.origin, offset);
//	return (out);
//}

#ifdef SMOOTH_SHADOWS

t_light	adjust_light(t_light light)
{
	double	phi;
	double	costheta;
	double	theta;
	double	r;
	t_vec	offset;

	phi = ft_rand() * 2 * M_PI;
	costheta = ft_rand() * 2 - 1;
	theta = acos(costheta);
	r = light.radius * cbrt(ft_rand());
	offset = new_vec(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi),
			r * cos(theta));
	light.origin = add_t(light.origin, offset);
	return (light);
}
#elif HARD_SHADOWS

t_light	adjust_light(t_light light)
{
	return (light);
}
#else

# error "No Shadows macro defined"

#endif // SOFT_SHADOWS HARD_SHADWOS

bool	in_light_fov(t_light light, t_point point)
{
	t_vec	ray_direct;
	double	cosine;

	if (light.type == POINT_LIGHT)
		return (true);
	if (eq_t(light.origin, point))
		return (true);
	ray_direct = norm(sub_t(light.origin, point));
	cosine = dot_prod(ray_direct, light.direct);
	if (fabs(cosine) > light.cosine_range)
		return (true);
	return (false);
}

t_fcolor	eng_ambient42(t_world world, t_fcolor color_at)
{
	return (mult_fcolor(world.ambient42, color_at));
}

void	calculate_color(t_shade_hit_norm *n)
{
	n->color = add_fcolor(n->color, n->surface);
	n->color = add_fcolor(n->color, n->reflected);
	n->color = add_fcolor(n->color, n->refracted);
}
