/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objs_to_world.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:01 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:34:02 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <libft.h>
#include <main.h>

static void	add_light_to_world(t_world *world, t_light *light)
{
	gc_dyn_arr_add_save((void **)(&world->lights), light, world->light_count++);
	if (!world->lights)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
}

static void	add_shape_to_world(t_world *world, t_obj_ptr obj_data, \
		size_t obj_size)
{
	t_obj_ptr	new;

	new = eng_alloc_shape(obj_data->type);
	ft_memcpy(new, obj_data, obj_size);
	gc_dyn_arr_add_save((void **)(&world->objs), (void *)(&new),
		world->obj_count++);
	if (!world->objs)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
}

void	eng_add_obj_to_world(t_world *world, t_obj_ptr obj)
{
	if (obj->type == OBJ_LIGHT)
		add_light_to_world(world, (t_light *)obj);
	else if (obj->type == OBJ_SPHERE)
		add_shape_to_world(world, (t_obj_ptr)obj, sizeof(t_sphere));
	else if (obj->type == OBJ_PLANE)
		add_shape_to_world(world, (t_obj_ptr)obj, sizeof(t_plane));
	else if (obj->type == OBJ_CYLINDER)
		add_shape_to_world(world, (t_obj_ptr)obj, sizeof(t_cylinder));
	else if (obj->type == OBJ_CONE)
		add_shape_to_world(world, (t_obj_ptr)obj, sizeof(t_cone));
	else
	{
		printf("type: %u\n", obj->type);
		ft_assert(0, __FILE__, __LINE__,
			"assert: add_obj_to_world: unsupported type");
	}
}