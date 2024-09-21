#include <main.h>

/* improvisted camera
*/
t_camera	eng_new_camera(double fov_x, t_point p, double wall_dist)
{
	t_camera camera;

	camera.base_obj = eng_new_obj();
	camera.base_obj.type = OBJ_CAMERA;
	camera.p = p;
	camera.fov_x = fov_x;
	camera.aspect_ratio = ASPECT_RATIO;
	camera.fov_y = 2 * atan(tan(fov_x / 2) / ASPECT_RATIO);
	camera.wall_dist = wall_dist;
	camera.wall_width = 2.0 * tan(camera.fov_x / 2) * camera.wall_dist;
	camera.wall_height = 2.0 * tan(camera.fov_y / 2) * camera.wall_dist;
	camera.wall_pixel_width = camera.wall_width / WIDTH;
	camera.wall_pixel_height = camera.wall_height / HEIGHT;
	return (camera);
}

void print_camera(t_camera *camera)
{
	print_t(1, camera->p);
	printf("Wall Distance: %f\n", camera->wall_dist);
	printf("Wall Width: %f\n", camera->wall_width);
	printf("Wall Height: %f\n", camera->wall_height);
	printf("FOV X: %f\n", camera->fov_x);
	printf("FOV Y: %f\n", camera->fov_y);
	printf("Aspect Ratio: %f\n", camera->aspect_ratio);
	printf("Wall Pixel Width: %f\n", camera->wall_pixel_width);
	printf("Wall Pixel Height: %f\n", camera->wall_pixel_height);
}

t_point	pixel_to_wall(t_camera *camera, size_t pixel_x, size_t pixel_y)
{
	t_point	ret;

	ret = new_point(0, 0, camera->wall_dist);
	ret.x = pixel_x * camera->wall_pixel_width + camera->wall_pixel_width / 2;
	ret.x -= camera->wall_width / 2;
	ret.y = pixel_y * camera->wall_pixel_height + camera->wall_pixel_height / 2;
	ret.y -= camera->wall_height / 2;
	return (ret);
}

void	eng_put_pixel(t_canvas *canvas, size_t x, size_t y, t_fcolor color)
{
	((t_uintcolor *)canvas->pixels)[y * WIDTH + x] = fcolor_to_uintcolor(color);
}

static void add_objs(t_world *world)
{
	t_sphere	sph;
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

	camera = eng_new_camera(fov_x, new_point(0, 0, -100), 10);


	for (size_t y = 0; y < canvas.height; y++)
	{
		for (size_t x = 0; x < canvas.width; x++)
		{
			t_point	wall_hit = pixel_to_wall(&camera, x, y);
			t_ray	camera_ray = eng_new_ray(camera.p, norm(sub_t(wall_hit, camera.p)));
			camera_ray.direct = norm(camera_ray.direct);
			color = eng_color_at(*world, camera_ray);
			eng_put_pixel(&canvas, x, y, color);
		}
		printf("y: %lu\n", y);
	}
	//store_as_plain_ppm(m_data, "EXAMPLE NAME.ppm");
}
