#include <ft_engine.h>
#include <main.h>
#include <libft.h>

t_world	eng_new_world(void)
{
	t_world	world;

	ft_bzero(&world, sizeof world);
	world.lights = gc_dyn_arr_init(sizeof(t_light), 0);
	world.light_count = 0;
	world.objs = gc_dyn_arr_init(sizeof(t_obj *), 0);
	world.obj_count = 0;
	return (world);
}

void	eng_init_engine(t_main *m_data, int ac, char *av[])
{
	t_engine	*engine;

	engine = &m_data->engine;
	engine->world = eng_new_world();
	engine->canvas = eng_new_canvas(m_data, WIDTH, HEIGHT);
	if (ac > 1)
	{
		parser(m_data, av[1]);
	}
}
