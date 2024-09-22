#include <main.h>

void	eng_put_pixel(t_canvas *canvas, size_t x, size_t y, t_fcolor color)
{
	((t_uintcolor *)canvas->pixels)[y * WIDTH + x] = fcolor_to_uintcolor(color);
}

static void add_objs(t_world *world)
{
	t_sphere		sph;
	t_light			light;
	t_fcolor		intensity;
	t_point			light_position;

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_translate(-5, 0, 0));
	sph.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&sph);

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_translate(-1, 3, 2));
	sph.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&sph);

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_translate(7, 0, 3));
	sph.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&sph);

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_translate(-1, -3, 7));
	sph.base_obj.material.fcolor = new_fcolor(3, 2, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&sph);

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_translate(3, -2, 5));
	sph.base_obj.material.fcolor = new_fcolor(0, 2, 1, 1);
	eng_add_obj_to_world(world, (t_obj *)&sph);

	light_position = new_point(0, 0, -10);
	intensity = new_fcolor(3, 1, 4, 1);
	light = eng_point_light(intensity, light_position);
	eng_add_obj_to_world(world, (t_obj *)&light);

	light_position = new_point(10, 10, -10);
	intensity = new_fcolor(1, 4, 1, 1);
	light = eng_point_light(intensity, light_position);
	eng_add_obj_to_world(world, (t_obj *)&light);
}

void	sphere_test(void *main_data)
{
	t_main			*m_data = (t_main *)main_data;
	double			fov_x = ((60.0 / 180) * M_PI);
	t_canvas		canvas = m_data->engine.canvas;
	t_camera		camera;
	t_world			*world;
	t_fcolor		color;

	static bool first = true;
	world = &m_data->engine.world;
	if (first)
	{
		first = false;
		add_objs(&m_data->engine.world);
	}

	camera = eng_new_camera(WIDTH, HEIGHT, fov_x);

	for (size_t y = 0; y < canvas.height; y++)
	{
		for (size_t x = 0; x < canvas.width; x++)
		{
			t_ray	camera_ray =eng_ray_for_pixel(camera, x, y);
			color = eng_color_at(*world, camera_ray);
			eng_put_pixel(&canvas, x, y, color);
		}
		printf("%f%%\n", ((float)y) / canvas.height * 100);
	}
	//store_as_plain_ppm(m_data, "EXAMPLE NAME.ppm");
}
