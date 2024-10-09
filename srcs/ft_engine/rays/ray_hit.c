/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:54 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:34:55 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>

// time in terms of how many direction vectors of the ray
t_point	eng_ray_pos(t_ray ray, double time)
{
	t_point	pos;

	pos = mult_v(ray.direct, time);
	pos = add_t(pos, ray.origin);
	return (pos);
}

// returns the index of the hit intersection
// returns -1 if there was no hit
t_intersc	*eng_ray_hit(t_intersc_arr *interscs)
{
	size_t	i;

	i = 0;
	while (i < interscs->count && interscs->arr[i].t < 0)
		i++;
	if (i < interscs->count)
		return (interscs->arr + i);
	return (NULL);
}