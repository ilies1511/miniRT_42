#include <main.h>

t_material	eng_new_material_polished_metal(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.05;
	mat.diffuse = 0.1;
	mat.specular = 0.9;
	mat.shininess = 300;
	mat.reflective = 1.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	return (mat);
}

static void add_objs(t_world *world)
{
	t_light	light_1 = eng_point_light(new_fcolor(1, 0.5, 0, 1), new_point(11, 10, -8));
	t_light	light_2 = eng_point_light(new_fcolor(0, 0.5, 1, 1), new_point(-5, 10, -1));
	t_sphere	sph1 = eng_new_glass_sphere();
	t_sphere	sph2 = eng_new_glass_sphere();
	t_plane		back = eng_new_plane();
	t_plane		bot = eng_new_plane();
	t_cylinder	cyl = eng_new_cylinder();
	t_cylinder	cyl2 = eng_new_cylinder();

	sph1.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj *)&sph1, mtx_translate(-6, 3, 0));
	eng_set_transform((t_obj *)&sph1, mtx_scale(3, 3, 3));

	sph2.base_obj.material.refractive_index = 1.00029;
	sph2.base_obj.material.reflective = 0.5;
	sph2.base_obj.material.transparency = 1.0;
	back.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	eng_set_transform((t_obj *)&sph2, mtx_translate(-6, 3, 0));
	eng_set_transform((t_obj *)&back, mtx_translate(0, 0, 10));
	eng_set_transform((t_obj *)&back, mtx_rotation_x(M_PI_2));

	bot = eng_new_plane();
	bot.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	bot.base_obj.material.reflective = 0.03;
	bot.base_obj.material.pattern = pat_checker2d_pattern(new_fcolor(1, 0, 0, 1), new_fcolor(0,0,1, 1));
	eng_set_transform((t_obj *)&bot, mtx_rotation_x(M_PI));
	eng_set_transform((t_obj *)&bot, mtx_translate(0, 0, 4));

	//cyl.base_obj.material = eng_new_material_polished_metal();
	cyl.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&cyl, mtx_scale(3, 3, 3));
	cyl.max = 5;
	eng_set_transform((t_obj *)&cyl, mtx_translate(4, 0, -6));

	//cyl.base_obj.material = eng_new_material_polished_metal();
	cyl2.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&cyl2, mtx_scale(3, 3, 3));
	cyl2.max = 1.5;
	eng_set_transform((t_obj *)&cyl2, mtx_translate(1, 0, -9));

	eng_add_obj_to_world(world, (t_obj *)&light_1);
	eng_add_obj_to_world(world, (t_obj *)&light_2);
	eng_add_obj_to_world(world, (t_obj *)&sph1);
	eng_add_obj_to_world(world, (t_obj *)&sph2);
	eng_add_obj_to_world(world, (t_obj *)&back);
	eng_add_obj_to_world(world, (t_obj *)&bot);
	eng_add_obj_to_world(world, (t_obj *)&cyl);
	eng_add_obj_to_world(world, (t_obj *)&cyl2);
}

void	sphere_test(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;

	camera = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)&camera, sc_transforme_view(new_point(0, 10, -70),
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
