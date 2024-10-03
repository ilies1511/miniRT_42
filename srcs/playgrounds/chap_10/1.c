#include <main.h>

t_material	eng_new_material_matte(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.1;
	mat.shininess = 10;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1;
	return (mat);
}

t_material	eng_new_dirty_water_material(void)
{
	t_material	mat;

	mat.fcolor.r = 0.5;
	mat.fcolor.g = 0.5;
	mat.fcolor.b = 0.4;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.3;
	mat.diffuse = 0.7;
	mat.specular = 0.5;
	mat.shininess = 50;
	mat.reflective = 0.1;
	mat.transparency = 0.7;
	mat.refractive_index = 1.33;
	return (mat);
}

t_material	eng_new_material_dark_wood(void)
{
	t_material	mat;

	mat.fcolor.r = 0.36;
	mat.fcolor.g = 0.25;
	mat.fcolor.b = 0.20;
	mat.fcolor.a = 1.0;
	mat.pattern = NULL;
	mat.ambient = 0.3;
	mat.diffuse = 0.6;
	mat.specular = 0.2;
	mat.shininess = 50;
	mat.reflective = 0.1;
	mat.transparency = 0.0;
	mat.refractive_index = 1.0;
	return (mat);
}

t_material	eng_dark_tree_stump(void)
{
	t_material	mat;

	mat.fcolor.r = 0.3;
	mat.fcolor.g = 0.2;
	mat.fcolor.b = 0.1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.5;
	mat.diffuse = 0.7;
	mat.specular = 0.0;
	mat.shininess = 50;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1;
	return (mat);
}

static void add_objs(t_world *world)
{
	t_light		light;
	t_light		light2;
	t_light		light3;
	t_plane		ceil;
	t_plane		top;
	t_plane		left_top;

	t_sphere	sph_mid;
	t_sphere	sph_mid2;
	t_sphere	sph_right;
	t_sphere	sph_left;

	t_cylinder	cyl;

	cyl = eng_new_cylinder();
	cyl.min = -0.5;
	cyl.max = 2;
	cyl.closed = true;
	//cyl.base_obj.material.transparency = 1.0;
	//cyl.base_obj.material.refractive_index = 1.5;
	//cyl.base_obj.material.reflective = 0.3;
	//cyl.base_obj.material.transparency = 1;
	//cyl.base_obj.material.refractive_index = 1.333;
	cyl.base_obj.material = eng_dark_tree_stump();

	//cyl.base_obj.material.pattern = pat_square3d_pattern(new_fcolor(0.5, 0.5, 0, 1), new_fcolor(0, 1, 1, 1));
	eng_set_transform((t_obj *)&cyl, mtx_translate(2, 0, -2));
	eng_add_obj_to_world(world, (t_obj *)&cyl);

	//sph_right = eng_new_sphere();
	sph_right = eng_new_glass_sphere();
	eng_set_transform((t_obj *)&sph_right, mtx_translate(1.5, 0.5, -0.5));
	eng_set_transform((t_obj *)&sph_right, mtx_scale(0.5, 0.5, 0.5));
	sph_right.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_right.base_obj.material.diffuse = 0.7;
	sph_right.base_obj.material.specular = 0.3;
	sph_right.base_obj.material.pattern = pat_checker3d_pattern(new_fcolor(1, 1, 1, 1), new_fcolor(0,0,0, 1));
	eng_set_transform((t_obj *)sph_right.base_obj.material.pattern, mtx_scale(0.1, 0.1, 0.1));

	eng_add_obj_to_world(world, (t_obj *)&sph_right);

	sph_mid = eng_new_glass_sphere();
	eng_set_transform((t_obj *)&sph_mid , mtx_translate(-0.5, 2, -3));
	sph_mid.base_obj.material = eng_new_material_dark_wood();
	//sph_mid.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	//sph_mid.base_obj.material.diffuse = 0.7;
	//sph_mid.base_obj.material.specular = 0.3;
	//sph_mid.base_obj.material.transparency = 0;
	//sph_mid.base_obj.material.reflective = 0.4;
	//sph_mid.base_obj.material.refractive_index = 1.33;
	//sph_mid.base_obj.material.pattern = pat_square3d_pattern(new_fcolor(1, 1, 0, 1), new_fcolor(0,1,1, 1));
	//eng_set_transform((t_obj *)sph_mid.base_obj.material.pattern, mtx_scale(0.1, 0.1, 0.1));
	//eng_set_transform((t_obj *)sph_mid.base_obj.material.pattern, mtx_rotation_y(M_PI_4));
	eng_add_obj_to_world(world, (t_obj *)&sph_mid);

	//sph_mid2 = eng_new_glass_sphere();
	//eng_set_transform((t_obj *)&sph_mid2 , mtx_translate(-0.5, 2, -3));
	//eng_set_transform((t_obj *)&sph_mid2 , mtx_scale(0.3, 0.3, 0.3));
	//sph_mid2.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	//sph_mid2.base_obj.material.diffuse = 0.7;
	//sph_mid2.base_obj.material.specular = 0.3;
	//sph_mid2.base_obj.material.transparency = 0.3;
	//sph_mid2.base_obj.material.reflective = 0;
	//sph_mid2.base_obj.material.pattern = pat_square3d_pattern(new_fcolor(1, 1, 0, 1), new_fcolor(0,1,1, 1));
	//eng_add_obj_to_world(world, (t_obj *)&sph_mid2);

	sph_left = eng_new_sphere();
	eng_set_transform((t_obj *)&sph_left, mtx_translate(-1.5, 0.33, -0.75));
	eng_set_transform((t_obj *)&sph_left, mtx_scale(0.33, 0.33, 0.33));
	sph_left.base_obj.material.fcolor = new_fcolor(1, 0.83984375, 0, 1);
	sph_left.base_obj.material.diffuse = 0.7;
	// sph_left.base_obj.material.shininess = 500;
	sph_left.base_obj.material.specular = 0.98;
	sph_left.base_obj.material.reflective = 0.7;
	//sph_left.base_obj.material.pattern = pat_checker3d_pattern(new_fcolor(0, 1, 0, 1), new_fcolor(1,0,1, 1));
	//eng_set_transform((t_obj *)sph_left.base_obj.material.pattern, mtx_scale(0.1, 0.1, 0.1));

	eng_add_obj_to_world(world, (t_obj *)&sph_left);

	ceil = eng_new_plane();
	ceil.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
	ceil.base_obj.material.pattern = pat_square3d_pattern(new_fcolor(1, 1, 0, 1), new_fcolor(0,1,1, 1));
	ceil.base_obj.material.reflective = 0.3;
	eng_add_obj_to_world(world, (t_obj *)&ceil);


	top = eng_new_plane();
	top.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	top.base_obj.material.reflective = 0.3;
	top.base_obj.material.pattern = pat_checker2d_pattern(new_fcolor(1, 0, 0, 1), new_fcolor(0,0,1, 1));
	//top.base_obj.material.transparency = 0.1;
	//***why is this buggy***
	eng_set_transform((t_obj *)&top, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj *)&top, mtx_translate(0, 0, 4));
	//***but this not ***
	//eng_set_transform((t_obj *)&top, mtx_translate(0, 0, 4));
	//eng_set_transform((t_obj *)&top, mtx_rotation_x(M_PI_2));
	//*******************
	eng_add_obj_to_world(world, (t_obj *)&top);

	left_top = eng_new_plane();
	left_top.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj *)&left_top, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj *)&left_top, mtx_rotation_y(M_PI + M_PI_2 + M_PI_4));
	eng_set_transform((t_obj *)&left_top, mtx_translate(-5, 0, 0));

	//eng_add_obj_to_world(world, (t_obj *)&left_top);

	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(9, 8, -5));
	light.radius = 0.5;
	eng_add_obj_to_world(world, (t_obj *)&light);

	//light2 = eng_point_light(new_fcolor(0, 0.7, 0, 1), new_point(-2, 10, -1));
	//eng_add_obj_to_world(world, (t_obj *)&light2);

	//light3 = eng_point_light(new_fcolor(0, 0, 0.5, 1), new_point(-5, 10, -1));
	//eng_add_obj_to_world(world, (t_obj *)&light3);
	(void)light2;
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
	//store_as_plain_ppm(m_data, "asd.ppm");
}
