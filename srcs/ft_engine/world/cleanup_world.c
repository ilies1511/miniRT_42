#include <ft_engine.h>
#include <libft.h>

void	eng_cleanup_world(t_world *world)
{
	dyn_arr_free((void **)(&world->lights));
	world->light_count = 0;
	dyn_arr_free((void **)(&world->objs));
	world->obj_count = 0;
}
