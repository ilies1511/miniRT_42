/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:56 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:36:57 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <ft_patterns.h>

t_light	eng_spot_light(t_fcolor intensity, t_point position,
		t_point look_at, double fov_360)
{
	t_light	light;
	double	rad_angle;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	light.base_obj.type = OBJ_LIGHT;
	light.radius = 1;
	light.type = SPOT_LIGHT;
	light.direct = sub_t(look_at, position);
	light.direct = norm(light.direct);
	rad_angle = fov_360 / 180 * M_PI / 2;
	light.cosine_range = cos(rad_angle);
	return (light);
}