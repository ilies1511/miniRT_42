#include <main.h>
#include <ft_material.h>
#include <ft_scene.h>

static void	init_world(t_world *world)
{

	t_light sun_light = eng_point_light(
		new_fcolor(1.00001, 0.900001, 0.60000001, 1),   // Warm, bright sunlight color
		new_point(0, 100, 20)       // High and behind the camera to simulate the angle of sunlight
	);
	t_sphere sph_glass = eng_new_glass_sphere();

	eng_set_transform((t_obj_ptr)&sph_glass, mtx_scale(1000.000001, 1000.00001, 1000.00001));
	sun_light.radius = 20.0001;
	t_plane	water = eng_new_plane();

	water.base_obj.material = eng_water();

	eng_set_transform((t_obj_ptr)&water, mtx_translate(0.00000001, 0.0000001, 0.000001));  // At horizon level

	t_plane floor = eng_new_plane();
	floor.base_obj.material = eng_sand();
	//floor.base_obj.material.pattern = pat_checker2d_pattern(
	//    new_fcolor(0.18, 0.31, 0.31, 1), floor.base_obj.material.fcolor);
	eng_set_transform((t_obj_ptr)&floor, mtx_translate(0.0000001, -40.000001, 0.000001));  // Below the water level


	t_plane		sky = eng_new_plane();
	sky.base_obj.material = eng_blue_sky();
	eng_set_transform((t_obj_ptr)&sky, mtx_translate(0.0000001, 100000000.00001, 0.000001));

	t_sphere	ball = eng_new_sphere();
	ball.base_obj.material = material_silver_and_gold();
	eng_set_transform((t_obj_ptr)&ball, mtx_translate(200, 3, -570));
	eng_set_transform((t_obj_ptr)&ball, mtx_scale(2, 2, 2));

	t_sphere	sph = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr)&sph, mtx_translate(196, 3, -570));
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(2, 2, 2));

	eng_add_obj_to_world(world, (t_obj_ptr)&sun_light);
	eng_add_obj_to_world(world, (t_obj_ptr)&water);
	eng_add_obj_to_world(world, (t_obj_ptr)&sky);
	eng_add_obj_to_world(world, (t_obj_ptr)&floor);
	eng_add_obj_to_world(world, (t_obj_ptr)&ball);
	eng_add_obj_to_world(world, (t_obj_ptr)&sph);


	eng_add_obj_to_world(world, (t_obj_ptr)&ball);

	t_sphere	sph2 = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(0.5, 0.5, 0.5));
	eng_set_transform((t_obj_ptr)&sph, mtx_translate(-11, 4, 5));
	eng_set_transform((t_obj_ptr)&sph2, mtx_translate(195, 7, -570));
	eng_set_transform((t_obj_ptr)&sph2, mtx_translate(-10, 0, 5));

	//sph.base_obj.material.reflective = 0.4;
	sph.base_obj.material.reflective = 0.6;
	sph2.base_obj.material.refractive_index = 1.000293;
	sph2.base_obj.material.transparency = 1;
	sph2.base_obj.material.reflective = 1;
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(2, 2, 2));
	eng_add_obj_to_world(world, (t_obj_ptr)&sph);
	eng_add_obj_to_world(world, (t_obj_ptr)&sph2);

	sph.base_obj.material.refractive_index = 1.33;
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(0.5, 0.5, 0.5));
	eng_set_transform((t_obj_ptr)&sph2, mtx_translate(-10, 0, 5));
	eng_set_transform((t_obj_ptr)&sph, mtx_translate(-10, 0, 5));
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(2, 2, 2));
	eng_add_obj_to_world(world, (t_obj_ptr)&sph);
	eng_add_obj_to_world(world, (t_obj_ptr)&sph2);
}

static void	init_camera(t_main *m_data)
{
	t_camera	*camera;

	camera = &(m_data->engine.camera);
	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
	*(camera) = eng_new_camera(m_data->engine.canvas.width, \
		m_data->engine.canvas.height, M_PI / 3);
	printf("WIDTH: %lu\nHEIGHT: %lu\n", m_data->engine.canvas.width, m_data->engine.canvas.height);
	eng_set_transform((t_obj_ptr)camera, sc_transforme_view(
	new_point(200, 5, -600),  // Slightly elevated to provide a better view of the horizo
	new_point(0, 0, 0),   // Looking slightly downwards towards the horizon
	new_vec(0, 1, 0)       // Keeping the 'up' vector to maintain vertical orientation
	));
}

void	demo_add_ocean_balls(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_world			*world;

	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
	//store_as_plain_ppm(m_data, "asd.ppm");
}
