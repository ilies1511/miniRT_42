#include <ft_engine.h>
#include <main.h>
#include <libft.h>

t_world	eng_new_world(void)
{
	t_world	world;

	ft_bzero(&world, sizeof world);
	world.lights = dyn_arr_init(sizeof(t_light), 0);
	world.light_count = 0;
	world.objs = dyn_arr_init(sizeof(t_obj *), 0);
	world.obj_count = 0;
	return (world);
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
	engine->world = eng_new_world();
	engine->canvas = eng_new_canvas(m_data, WIDTH, HEIGHT);
}
