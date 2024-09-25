#include <main.h>

static void add_objs(t_world *world)
{
	t_light		light;
	t_light		light2;
	t_plane		ceil;
	t_plane		top;
	t_plane		left_top;

	t_sphere	sph_mid;
	t_sphere	sph_right;
	t_sphere	sph_left;

	sph_right = eng_new_sphere();
	eng_set_transform((t_obj *)&sph_right, mtx_translate(1.5, 0.5, -0.5));
	eng_set_transform((t_obj *)&sph_right, mtx_scale(0.5, 0.5, 0.5));
	sph_right.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_right.base_obj.material.diffuse = 0.7;
	sph_right.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj *)&sph_right);

	sph_mid = eng_new_sphere();
	eng_set_transform((t_obj *)&sph_mid , mtx_translate(-0.5, 1, 0.5));
	sph_mid.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_mid.base_obj.material.diffuse = 0.7;
	sph_mid.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj *)&sph_mid);

	sph_left = eng_new_sphere();
	eng_set_transform((t_obj *)&sph_left, mtx_translate(-1.5, 0.33, -0.75));
	eng_set_transform((t_obj *)&sph_left, mtx_scale(0.33, 0.33, 0.33));
	sph_left.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_left.base_obj.material.diffuse = 0.7;
	// sph_left.base_obj.material.shininess = 500;
	sph_left.base_obj.material.specular = 0.3;
	eng_add_obj_to_world(world, (t_obj *)&sph_left);

	ceil = eng_new_plane();
	ceil.base_obj.material.fcolor = new_fcolor(0, 1, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&ceil);


	top = eng_new_plane();
	top.base_obj.material.fcolor = new_fcolor(1, 1, 0, 1);
	//***why is this buggy***
	//eng_set_transform((t_obj *)&top, mtx_rotation_x(M_PI_2));
	//eng_set_transform((t_obj *)&top, mtx_translate(0, 0, 4));
	//***but this not ***
	eng_set_transform((t_obj *)&top, mtx_translate(0, 0, 4));
	eng_set_transform((t_obj *)&top, mtx_rotation_x(M_PI_2));
	//*******************
	eng_add_obj_to_world(world, (t_obj *)&top);

	left_top = eng_new_plane();
	left_top.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&left_top, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj *)&left_top, mtx_rotation_y(M_PI + M_PI_2 + M_PI_4));
	eng_set_transform((t_obj *)&left_top, mtx_translate(-5, 0, 0));
	//eng_add_obj_to_world(world, (t_obj *)&left_top);

	light = eng_point_light(new_fcolor(1, 0, 0, 1), new_point(5, 5, -5));
	eng_add_obj_to_world(world, (t_obj *)&light);

	light2 = eng_point_light(new_fcolor(0, 0, 1, 1), new_point(3, 4, -1));
	eng_add_obj_to_world(world, (t_obj *)&light2);
}

void	sphere_test(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;

	camera = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)&camera, sc_transforme_view(new_point(5, 5, -5),
			new_point(0, 0, 0), new_vec(0.3, 0.3, 0.3)));
	static bool first = true;
	world = &m_data->engine.world;
	if (first)
	{
		first = false;
		add_objs(world);
	}
	eng_render(camera, *world, canvas);
	// store_as_plain_ppm(m_data, "d.ppm");
}
