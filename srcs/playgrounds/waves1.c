#include <main.h>

static t_material	eng_new_material_polished_metal(void)
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
	mat.reflective = 0.3;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	return (mat);
}

static t_material	material123(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.fcolor = new_fcolor(1, 0.843, 0, 1);
	mat.pattern = pat_stripe_pattern(new_fcolor(1, 1, 1, 1), new_fcolor(1, 0.843, 0, 1));
	mat.pattern = NULL;
	mat.ambient = 0.05;
	mat.diffuse = 0.1;
	mat.specular = 0.9;
	mat.shininess = 300;
	mat.reflective = 0.9;
	mat.transparency = 0.0;
	mat.refractive_index = 1.52;
	return (mat);
}

static t_material	eng_blue_sky(void)
{
	t_material	mat;

	mat.fcolor.r = 4.0 / 255;
	mat.fcolor.g = 100.0 / 255;
	mat.fcolor.b = 280.0 / 255;
	//mat.fcolor.r = 0.2;
	//mat.fcolor.g = 0;
	//mat.fcolor.b = 1;

	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 1.3;
	mat.diffuse = 1;
	mat.specular = 0;
	mat.shininess = 0;
	mat.reflective = 0;
	mat.transparency = 0;
	mat.refractive_index = 1.000;
	return (mat);
}

static t_material	eng_water(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;

	mat.fcolor.r = 0.2;
	mat.fcolor.g = 0.5;
	mat.fcolor.b = 0.7;

	mat.pattern = NULL;
	mat.bump = bump_wave();
	//mat.bump = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 400;
	mat.reflective = 0.5;
	mat.transparency = 0.4;
	mat.refractive_index = 1.333;
	return (mat);
}


static t_material	eng_sand(void)
{
	t_material	mat;

	mat.fcolor.r = 0.76;
	mat.fcolor.g = 0.7;
	mat.fcolor.b = 0.5;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	// mat.bump = bump_wave();
	mat.bump = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.7;
	mat.specular = 0.1;
	mat.shininess = 10;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1.00029;
	return (mat);
}

//static void add_objs(t_world *world)
//{
//	// t_light	light_1 = eng_point_light(new_fcolor(253.0 / 255, 251.0 / 255, 211.0/255, 1),
//	// 	new_point(0, 5000, 50000));
//	t_light	light_1 = eng_point_light(new_fcolor(253.0 / 255, 251.0 / 255, 211.0/255, 1),
//		new_point(0, 5000, 5000));
//	t_plane		water = eng_new_plane();
//	t_plane		floor = eng_new_plane(); t_plane		sky = eng_new_plane();
//
//	// bot.base_obj.material.reflective = 0.2;
//	water.base_obj.material = eng_water();
//	//bot.base_obj.material.pattern = pat_checker2d_pattern(new_fcolor(1, 0, 0, 1), new_fcolor(0,0,1, 1));
//
//	sky.base_obj.material = eng_blue_sky();
//	eng_set_transform((t_obj_ptr)&sky, mtx_translate(0, 50, 0));
//
//	//floor.base_obj.material.fcolor = new_fcolor(48.0 / 255, 213 / 255.0, 200 / 255.0, 1);
//	floor.base_obj.material = eng_sand();
//	eng_set_transform((t_obj_ptr)&floor, mtx_translate(0, -40, 0));
//
//	eng_add_obj_to_world(world, (t_obj_ptr)&light_1);
//	eng_add_obj_to_world(world, (t_obj_ptr)&water);
//	//eng_add_obj_to_world(world, (t_obj_ptr)&sky);
//	eng_add_obj_to_world(world, (t_obj_ptr)&floor);
//}

static void add_objs(t_world *world)
{

t_light sun_light = eng_point_light(
    new_fcolor(1.0, 0.9, 0.6, 1),   // Warm, bright sunlight color
    new_point(0, 100, 20)       // High and behind the camera to simulate the angle of sunlight
);
	t_sphere sph_glass = eng_new_glass_sphere();
	
	eng_set_transform((t_obj_ptr)&sph_glass, mtx_scale(1000, 1000, 1000));
	sun_light.radius = 20;
	t_plane	water = eng_new_plane();

	water.base_obj.material = eng_water();
	
	//water.base_obj.material.reflective = 0.6;
	//water.base_obj.material.transparency = 0.7;
	//water.base_obj.material.refractive_index = 1.33; // Approximate for water
	eng_set_transform((t_obj_ptr)&water, mtx_translate(0, 0, 0));  // At horizon level

	t_plane floor = eng_new_plane();
	floor.base_obj.material = eng_sand();
	//floor.base_obj.material.pattern = pat_checker2d_pattern(
	//    new_fcolor(0.18, 0.31, 0.31, 1), floor.base_obj.material.fcolor);
	eng_set_transform((t_obj_ptr)&floor, mtx_translate(0, -40, 0));  // Below the water level
	
	
	t_plane		sky = eng_new_plane();
	sky.base_obj.material = eng_blue_sky();
	eng_set_transform((t_obj_ptr)&sky, mtx_translate(0, 10000000, 0));
	
	t_sphere	ball = eng_new_sphere();
	ball.base_obj.material = material123();
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
	//eng_set_transform((t_obj_ptr)&sph, mtx_translate(0, 0, 10));
	//eng_set_transform((t_obj_ptr)&sph, mtx_scale(2, 2, 2));
	//eng_add_obj_to_world(world, (t_obj_ptr)&sph);
}

void	sphere_test(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;

	camera = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
//	eng_set_transform((t_obj_ptr)&camera, sc_transforme_view(new_point(0, 2, -30),
//			new_point(0, 0, 0), new_vec(0, 1, 0)));

eng_set_transform((t_obj_ptr)&camera, sc_transforme_view(
    new_point(200, 5, -600),  // Slightly elevated to provide a better view of the horizo
    new_point(0, 0, 0),   // Looking slightly downwards towards the horizon
    new_vec(0, 1, 0)       // Keeping the 'up' vector to maintain vertical orientation
));
	static bool first = true;
	world = &m_data->engine.world;
	if (first)
	{
		first = false;
		add_objs(world);
	}
	eng_render(camera, *world, canvas);
	store_as_plain_ppm(m_data, "ocean1.ppm");
}
