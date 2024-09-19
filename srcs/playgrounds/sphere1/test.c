#include <main.h>

void	sphere_test(void *main_data)
{
	t_main	*m_data = (t_main *)main_data;
	t_uint_color	color;
	t_uint_color	*pixels = (t_uint_color *)m_data->canvas.img->pixels;
	t_ray			ray_base;
	static t_sphere		sph;
	static bool			first = true;

	double	base_x_angle = 0;
	double	base_y_angle = 0;

	if (first)
	{
		first = false;
		sph = eng_new_sphere();
	}
	//eng_set_transform((t_obj *)&sph, mtx_scale(1.1, 1, 1));
	ray_base = eng_new_ray(new_point(0, 0, -4), new_vec(0, 0, 1));
	//t_ray tmp;
	//static double	 rotation = 0;
	//eng_set_transform((t_obj *)&ray_base, mtx_rotation_y(rotation));
	//rotation += M_PI_4;
	//rotation = fmod(rotation, 2 * M_PI);
	//eng_transform((t_obj *)&ray_base, (t_obj *)&tmp);
	//ray_base = tmp;
	t_intersc_arr	interscs = eng_new_intersc_arr();



	const double fov_x = (60.0 / 360) * 2 * M_PI;
	const double fov_y = (60.0 / 360) * 2 * M_PI;


	color.full = RED;
	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			t_ray	ray = ray_base;
			double	cur_x_angle = base_x_angle - fov_x / 2 + (float)x / WIDTH * fov_x;
			cur_x_angle = fmod(cur_x_angle, 2 * M_PI);
			eng_set_transform((t_obj *)&ray, mtx_rotation_x(cur_x_angle));
			double	cur_y_angle = base_y_angle - fov_y / 2 + (float)y / HEIGHT * fov_y;
			cur_y_angle = fmod(cur_y_angle, 2 * M_PI);
			eng_set_transform((t_obj *)&ray, mtx_rotation_y(cur_y_angle));
			ray.direct = mtx_mult_mt(ray.base_obj.transform, ray.direct);
			eng_intersc_ray(&interscs, &ray, (t_obj *) &sph);
			t_intersc	*intersc = eng_ray_hit(&interscs);
			if (intersc)
			{
				//t_point	intersc_p = add_t(ray.origin, mult_v(ray.direct, intersc->t));
				//t_vec	rad_v = sub_t(sph.origin, intersc_p);
				//float	dot = dot_prod(norm(rad_v), norm(ray.direct));
				//if (dot < 0)
				{
					//color.full = WHITE;
					//color.argb.r *= -dot;
					//color.argb.g *= -dot;
					//color.argb.b *= -dot;
					pixels[y * WIDTH + x] = color;
				}
			}
			eng_free_intersc_arr(&interscs);
		}
		printf("y: %lu\n", y);
	}
	//store_as_plain_ppm(m_data, "ENTER FILE NAME TO DOCUMENT PROGRESS.ppm");
	
	//base_x_angle = fmod(base_x_angle, 2 * M_PI);
	//base_y_angle = fmod(base_x_angle, 2 * M_PI);
	//base_y_angle += M_PI_4 / 4;
	//base_x_angle += M_PI_4 / 3;
}

