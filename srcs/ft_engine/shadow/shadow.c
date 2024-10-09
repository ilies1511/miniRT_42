/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:10 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:34:11 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>

bool	eng_is_shadowed(t_world world, t_point point, t_light light)
{
	t_vec			direction;
	t_point			delta;
	double			distance;
	t_intersc_arr	intersecs;
	t_intersc		*intersec;

	delta = sub_t(light.origin, point);
	direction = new_vec(delta.x, delta.y, delta.z);
	distance = len_v(direction);
	direction = norm(direction);
	intersecs = eng_new_intersc_arr();
	eng_ray_intersc_world(eng_new_ray(point, direction), world, &intersecs);
	intersec = eng_ray_hit(&intersecs);
	if (intersec && intersec->t < distance)
		return (eng_free_intersc_arr(&intersecs), true);
	return (eng_free_intersc_arr(&intersecs), false);
}