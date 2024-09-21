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
	((t_uintcolor *)canvas->img->pixels)[y * WIDTH + x] = fcolor_to_uintcolor(color);
}
//TODO: Entweder material direkt (ueberall) im obj struct rein ODER helper fnc (input obj output material)
void	sphere_test(void *main_data)
{
	t_main		*m_data = (t_main *)main_data;
	static t_sphere	sph;
	static bool	first = true;
	double		fov_x = ((60.0 / 180) * M_PI);
	t_canvas	canvas = m_data->canvas;
	static t_camera	camera;
	t_light		light;
	t_light		light2;
	t_fcolor	intensity;
	t_point		light_position;
	t_point		hit_position;
	t_vec		normal;
	t_vec		eyev;

	light_position = new_point(-10, 10, -10);
	intensity = new_fcolor(1, 1, 1, 1);
	light = eng_point_light(intensity, light_position);
	light_position = new_point(10, 10, -10);
	intensity = new_fcolor(1, 0, 0, 1);
	light2 = eng_point_light(intensity, light_position);
	if (first)
	{
		first = false;
		sph = eng_new_sphere();
		camera = eng_new_camera(fov_x, new_point(0, 0, -5), 10);
		eng_set_transform((t_obj *)&sph, mtx_translate(-1, 0, 0));
		eng_set_transform((t_obj *)&camera, mtx_rotation_y(M_PI_4 / 16));
	}
	t_fcolor color = new_fcolor(1, 0, 0, 1);

	t_intersc_arr	interscs = eng_new_intersc_arr();

	eng_transform((t_obj *)&camera, NULL);
	for (size_t y = 0; y < canvas.height; y++)
	{
		for (size_t x = 0; x < canvas.width; x++)
		{
			t_point	wall_hit = pixel_to_wall(&camera, x, y);
			t_ray	camera_ray = eng_new_ray(camera.p, norm(sub_t(wall_hit, camera.p)));
			camera_ray.direct = norm(camera_ray.direct);
			eng_intersc_ray(&interscs, &camera_ray, (t_obj *)&sph);
			eng_sort_intersc(&interscs);
			t_intersc	*intersc = eng_ray_hit(&interscs);
			if (intersc)
			{
				hit_position = eng_ray_pos(camera_ray, intersc->t);
				normal = eng_normal_at(intersc->obj, hit_position);
				eng_put_pixel(&canvas, x, y, color);
				eyev = negate_v(camera_ray.direct);
				color = eng_lighting(sph.material, light, hit_position, eyev, normal);
				// color = add_fcolor(color, eng_lighting(sph.material, light2, hit_position, eyev, normal));
				eng_put_pixel(&canvas, x, y, color);
			}
			eng_free_intersc_arr(&interscs);
		}
		//printf("y: %lu\n", y);
	}
	store_as_plain_ppm(m_data, "phong_lighting_onesource.ppm");
}
