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

t_material	material123(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = pat_stripe_pattern(new_fcolor(1, 1, 1, 1), new_fcolor(1, 0.843, 0, 1));
	mat.ambient = 0.05;
	mat.diffuse = 0.1;
	mat.specular = 0.9;
	mat.shininess = 300;
	mat.reflective = 0.9;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	return (mat);
}

t_material	eng_blue_sky(void)
{
	t_material	mat;

	mat.fcolor.r = 0.53;
	mat.fcolor.g = 0.81;
	mat.fcolor.b = 0.92;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 1.0;
	mat.diffuse = 0.0;
	mat.specular = 0.0;
	mat.shininess = 0;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1.00029;
	return (mat);
}

static void add_objs(t_world *world)
{
	t_light	light_1 = eng_spot_light(new_fcolor(1, 1, 1, 1), new_point(11, 40, -40), new_point(-2, 0, -3), 30);
	//t_light	light_1 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, 0));
	t_light	light_2 = eng_point_light(new_fcolor(0.01, 0.01, 0.01, 1), new_point(-5, 10, -1));
	t_sphere	sph1 = eng_new_glass_sphere();
	t_sphere	sph2 = eng_new_glass_sphere();
	t_plane		back = eng_new_plane();
	t_plane		bot = eng_new_plane();
	t_plane		behind = eng_new_plane();
	t_cylinder	cyl = eng_new_cylinder();
	t_cylinder	cyl2 = eng_new_cylinder();
	t_cone		cone = eng_new_cone();
	
	t_sphere	test = eng_new_sphere();

	sph1.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj *)&sph1, mtx_translate(-6, 3, 0));
	eng_set_transform((t_obj *)&sph1, mtx_scale(3, 3, 3));

	sph2.base_obj.material.refractive_index = 1.00029;
	sph2.base_obj.material.reflective = 0.5;
	sph2.base_obj.material.transparency = 1.0;
	eng_set_transform((t_obj *)&sph2, mtx_translate(-6, 3, 0));

	//back.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	back.base_obj.material = material123();
	eng_set_transform((t_obj *)&back, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj *)&back, mtx_translate(0, 0, 10));

	//bot.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	//bot.base_obj.material.shininess = 0;
	//bot.base_obj.material.specular = 0;
	//bot.base_obj.material.ambient = 0;
	bot.base_obj.material.reflective = 0.2;
	bot.base_obj.material.pattern = pat_checker2d_pattern(new_fcolor(1, 0, 0, 1), new_fcolor(0,0,1, 1));
	eng_set_transform((t_obj *)&bot, mtx_translate(0, 0, 4));

	behind.base_obj.material = eng_blue_sky();
	eng_set_transform((t_obj *)&behind, mtx_translate(0, 0, -100));
	eng_set_transform((t_obj *)&behind, mtx_rotation_x(M_PI_2));

	cyl.base_obj.material = eng_new_material_polished_metal();
	//cyl.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&cyl, mtx_scale(3, 3, 3));
	cyl.max = 5;
	eng_set_transform((t_obj *)&cyl, mtx_translate(4, 0, -6));

	cyl2.base_obj.material = eng_new_material_polished_metal();
	//cyl2.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&cyl2, mtx_scale(3, 3, 3));
	cyl2.max = 1.5;
	eng_set_transform((t_obj *)&cyl2, mtx_translate(1, 0, -9));


	cone.min = 0;
	cone.max = 2;
	cone.closed = true;
	cone.origin = new_point(0, 20, 0);
	eng_set_transform((t_obj *)&cone, mtx_scale(3, 3, 3));
	//eng_set_transform((t_obj *)&cone , mtx_translate(0, -6, 15));
	//eng_set_transform((t_obj *)&cone , mtx_rotation_z(M_PI_2));
	//eng_set_transform((t_obj *)&cone , mtx_rotation_y(M_PI_2));

	//eng_set_transform((t_obj *)&cone , mtx_rotation_z(M_PI_2));
	//eng_set_transform((t_obj *)&cone , mtx_rotation_x(M_PI));
	//eng_set_transform((t_obj *)&cone , mtx_scale(0.1, 0.1, 0.1));

	eng_set_transform((t_obj *)&test, mtx_translate(0, 2, 15));
	

	eng_add_obj_to_world(world, (t_obj *)&light_1);
	//eng_add_obj_to_world(world, (t_obj *)&light_2);
	eng_add_obj_to_world(world, (t_obj *)&sph1);
	eng_add_obj_to_world(world, (t_obj *)&sph2);
	eng_add_obj_to_world(world, (t_obj *)&back);
	eng_add_obj_to_world(world, (t_obj *)&bot);
	eng_add_obj_to_world(world, (t_obj *)&cyl);
	eng_add_obj_to_world(world, (t_obj *)&cyl2);
	eng_add_obj_to_world(world, (t_obj *)&behind);
	//eng_add_obj_to_world(world, (t_obj *)&cone);
	//eng_add_obj_to_world(world, (t_obj *)&test);
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
	//eng_set_transform((t_obj *)&camera, sc_transforme_view(new_point(0, 20, -20),
	//		new_point(0, 0, 0), new_vec(0, 1, 1)));
	static bool first = true;
	world = &m_data->engine.world;
	if (first)
	{
		first = false;
		add_objs(world);
	}
	eng_render(camera, *world, canvas);
	store_as_plain_ppm(m_data, "spotlight.ppm");
}
