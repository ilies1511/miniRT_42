#include <ft_engine.h>
#include <main.h>
#include <libft.h>

void	init_world(t_world *world)
{
	world->lights = dyn_arr_init(sizeof(t_light), 1);
	world->light_count = 0;
	world->objs = dyn_arr_init(sizeof(t_obj *), 1);
	world->obj_count = 0;
}

void	cleanup_engine(t_engine *engine)
{
	cleanup_world(&engine->world);
	ft_bzero(engine, sizeof *engine);
}

void	eng_init_engine(t_main *m_data)
{
	t_engine	*engine;

	engine = &m_data->engine;
	//ft_bzero(engine, sizeof *engine);
	init_world(&engine->world);
	engine->canvas = eng_new_canvas(m_data, WIDTH, HEIGHT);
}
