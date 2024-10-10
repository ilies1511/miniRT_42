/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:28 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:36:29 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

void	eng_ray_set_objs_inverse(t_ray *ray, t_obj_ptr obj)
{
	ray->base_obj.transform = obj->inverse;
	ray->base_obj.inverse = obj->transform;
}

void	eng_set_transform(t_obj_ptr obj, t_matrix transform)
{
	obj->transform = mtx_mult_mm(obj->transform, transform);
	obj->inverse = mtx_inverse(obj->transform);
}

//*******mayebe something like this is needed later on****
/*
static void	set_transform_ray(t_ray *ray, t_matrix transform)
{
}

static void	set_transform_sphere(t_ray *ray, t_matrix transform)
{
}

void	set_transform(t_obj_ptr obj, t_matrix transform)
{
	if (obj->type == OBJ_RAY)
		set_transform_ray((t_ray *)obj, transform);
	else if (in->type == OBJ_SPHERE)
		set_transform_sphere((t_sphere *)obj, transform);
	else
		rt_assert(0, __FILE__, __LINE__, "Error: eng_transform: Invalid type");

}
*/
