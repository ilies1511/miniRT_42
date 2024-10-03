#include <main.h>

static void add_objs(t_world *world)
{
	t_light	light_1 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(1, 10, -1));
	t_sphere	sph1 = eng_new_glass_sphere();
	t_sphere	sph2 = eng_new_glass_sphere();
	t_plane		back = eng_new_plane();

	sph1.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj *)&sph1, mtx_scale(3, 3, 3));

	sph2.base_obj.material.refractive_index = 1.00029;
	sph2.base_obj.material.reflective = 0.5;
	sph2.base_obj.material.transparency = 1.0;

	back.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	eng_set_transform((t_obj *)&back, mtx_translate(0, 0, 10));
	eng_set_transform((t_obj *)&back, mtx_rotation_x(M_PI_2));


	eng_add_obj_to_world(world, (t_obj *)&light_1);
	eng_add_obj_to_world(world, (t_obj *)&sph1);
	eng_add_obj_to_world(world, (t_obj *)&sph2);
	eng_add_obj_to_world(world, (t_obj *)&back);
}

void	sphere_test(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;

	camera = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)&camera, sc_transforme_view(new_point(0, 0, -10),
			new_point(0, 0, 0), new_vec(0, 1, 0)));
	static bool first = true;
	world = &m_data->engine.world;
	if (first)
	{
		first = false;
		add_objs(world);
	}
	eng_render(camera, *world, canvas);
	//store_as_plain_ppm(m_data, "qwe.ppm");
}
