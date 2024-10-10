/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:41 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:36:42 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>
#include <ft_bump_map.h>

/*
	use case: unit circle sphere (sphere that was not tranformed yet)
*/
t_vec	compute_normal_sphere(t_point object_point)
{
	t_point	object_normal;

	object_normal = sub_t(object_point, new_point(0, 0, 0));
	return (object_normal);
}

t_vec	compute_normal_plane(t_point object_point)
{
	(void) object_point;
	return (new_vec(0, 1, 0));
}

t_vec	compute_normal_cylinder(t_cylinder *cylinder, t_point object_point)
{
	double	distance;

	rt_assert(cylinder->base_obj.type == OBJ_CYLINDER, \
		__FILE__, __LINE__, "wtf");
	distance = (object_point.x * object_point.x) + (object_point.z
			* object_point.z);
	if (distance < 1 && object_point.y >= cylinder->max - (EPSILON))
		return (new_vec(0, 1, 0));
	else if (distance < 1 && object_point.y <= cylinder->min + (EPSILON))
		return (new_vec(0, -1, 0));
	else
		return (new_vec(object_point.x, 0, object_point.z));
}

t_vec	compute_normal_cone(t_cone *cone, t_point object_point)
{
	double	distance;
	double	y;

	if (eq_t(object_point, new_point(0, 0, 0)))
		return (norm(new_vec(0, 1, 0)));
	distance = (object_point.x * object_point.x) + \
		(object_point.z * object_point.z);
	if (distance < 1 && object_point.y >= cone->max - (EPSILON))
		return (new_vec(0, 1, 0));
	else if (distance < 1 && object_point.y <= cone->min + (EPSILON))
		return (new_vec(0, -1, 0));
	else
	{
		y = sqrt((object_point.x * object_point.x) \
			+ (object_point.z * object_point.z));
		if (object_point.y > 0)
			y = -y;
		return (new_vec(object_point.x, y, object_point.z));
	}
}
