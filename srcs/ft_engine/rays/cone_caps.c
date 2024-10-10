/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:54 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:49:29 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <libft.h>

bool	check_cap_cone(t_ray ray, double t, double y)
{
	double	x;
	double	z;
	bool	result;

	x = ray.origin.x + t * ray.direct.x;
	z = ray.origin.z + t * ray.direct.z;
	if (y < 0)
		y = -y;
	result = (x * x) + (z * z) <= y;
	return (result);
}

//TODO: CHeck again
void	eng_intersc_ray_cone_caps(t_intersc_arr *intersecs, t_ray ray,
		t_cone *cone)
{
	double	t;
	double	t2;

	if (cone->closed == false)
		return ;
	t = (cone->min - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t, cone->max))
		eng_add_intersc(intersecs, (t_obj_ptr)cone, t);
	if (intersecs->count % 2 == 0)
	{
		t2 = (cone->max - ray.origin.y) / ray.direct.y;
		if (check_cap_cone(ray, t2, cone->max))
		{
			intersecs->arr[intersecs->count - 2].obj = (t_obj_ptr) & cone;
			intersecs->arr[intersecs->count - 2].t = t2;
		}
		return ;
	}
	t2 = (cone->max - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t2, cone->max))
		eng_add_intersc(intersecs, (t_obj_ptr)cone, t2);
}
