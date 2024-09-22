//#include <main.h>
//
//
//
//static void add_objs(t_world *world)
//{
//	t_sphere		sph;
//	t_light			light;
//	t_fcolor		intensity;
//	t_point			light_position;
//
//	sph = eng_new_sphere();
//	eng_set_transform((t_obj *)&sph, mtx_translate(-5, 0, 0));
//	sph.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
//	eng_add_obj_to_world(world, (t_obj *)&sph);
//
//	sph = eng_new_sphere();
//	eng_set_transform((t_obj *)&sph, mtx_translate(-1, 3, 2));
//	sph.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
//	eng_add_obj_to_world(world, (t_obj *)&sph);
//
//	sph = eng_new_sphere();
//	eng_set_transform((t_obj *)&sph, mtx_translate(7, 0, 3));
//	sph.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
//	eng_add_obj_to_world(world, (t_obj *)&sph);
//
//	sph = eng_new_sphere();
//	eng_set_transform((t_obj *)&sph, mtx_translate(-1, -3, 7));
//	sph.base_obj.material.fcolor = new_fcolor(3, 2, 1, 1);
//	eng_add_obj_to_world(world, (t_obj *)&sph);
//
//	sph = eng_new_sphere();
//	eng_set_transform((t_obj *)&sph, mtx_translate(3, -2, 5));
//	sph.base_obj.material.fcolor = new_fcolor(0, 2, 1, 1);
//	eng_add_obj_to_world(world, (t_obj *)&sph);
//
//	light_position = new_point(0, 0, -10);
//	intensity = new_fcolor(3, 1, 4, 1);
//	light = eng_point_light(intensity, light_position);
//	eng_add_obj_to_world(world, (t_obj *)&light);
//
//	light_position = new_point(10, 10, -10);
//	intensity = new_fcolor(1, 4, 1, 1);
//	light = eng_point_light(intensity, light_position);
//	eng_add_obj_to_world(world, (t_obj *)&light);
//}
//
//void	sphere_test(void *main_data)
//{
//	t_main			*m_data = (t_main *)main_data;
//	t_canvas		canvas = m_data->engine.canvas;
//	t_camera		camera;
//	t_world	*world;
//	static bool first = true;
//	static double angle_x1 = 0;
//	static double angle_y1 = 0;
//	static double angle_z1 = 0;
//	double angles[3] ={ M_PI / 33, M_PI / 37, M_PI / 47};
//
//	world = &m_data->engine.world;
//	if (first)
//	{
//		first = false;
//		add_objs(world);
//	}
//	camera = eng_new_camera(WIDTH, HEIGHT, M_PI_2);
//	eng_set_transform((t_obj *)&camera, mtx_translate(0, 0, -10));
//	eng_set_transform((t_obj *)&camera, mtx_rotation_x(angle_x1));
//	eng_set_transform((t_obj *)&camera, mtx_rotation_y(angle_y1));
//	eng_set_transform((t_obj *)&camera, mtx_rotation_z(angle_z1));
//	eng_render(camera , *world, canvas);
//	for (int i = 0; i < 5; i++)
//	{
//		eng_set_transform(world->objs[i], mtx_rotation_x(angle_x1  / (i + 1)));
//		eng_set_transform(world->objs[i], mtx_rotation_y(angle_x1 * (i + 1)));
//		eng_set_transform(world->objs[i], mtx_rotation_z(angle_x1 / (i + 0.123)));
//	}
//	angle_x1 += M_PI / 13;
//	angle_x1 -= M_PI / 13;
//	angle_y1 += M_PI / 23;
//	angle_z1 += M_PI / 13;
//
//	//store_as_plain_ppm(m_data, "EXAMPLE NAME.ppm");
//}
