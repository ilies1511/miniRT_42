#include <ft_engine.h>
#include <libft.h>
#include <main.h>

static void	add_light_to_world(t_world *world, t_light *light)
{
	dyn_arr_add_save((void **)(&world->lights), light, world->light_count++);
	if (!world->lights)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
}

static void	add_normal_obj_to_world(t_world *world, void *obj_data, size_t obj_size)
{
	uint8_t	*new;

	new = ft_malloc(obj_size);
	if (!new)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
	ft_memcpy(new, obj_data, obj_size);
	dyn_arr_add_save((void **)(&world->objs), (void *)(&new), world->obj_count++);
	if (!world->objs)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
}

void	eng_add_obj_to_world(t_world *world, t_obj *obj)
{
	if (obj->type == OBJ_LIGHT)
		add_light_to_world(world, (t_light *)obj);
	else if (obj->type == OBJ_SPHERE)
		add_normal_obj_to_world(world, (void *)obj, sizeof(t_sphere));
	else
	{
		printf("type: %u\n", obj->type);
		ft_assert(0, __FILE__, __LINE__,
			"assert: add_obj_to_world: unsupported type");
	}
}
