#include <main.h>

void	sphere_test_v1(void *main_data)
{
	t_main	*m_data = (t_main *)main_data;
	t_uintcolor	color;
	t_uintcolor	*pixels = (t_uintcolor *)m_data->engine.canvas.pixels;
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
	t_intersc_arr	interscs = eng_new_intersc_arr();



	const double fov_x = (60.0 / 360) * 2 * M_PI;
	const double fov_y = (60.0 / 360) * 2 * M_PI;


	color.full = RED;
	for (size_t y = 0; y < m_data->engine.canvas.height; y++)
	{
		for (size_t x = 0; x < m_data->engine.canvas.width; x++)
		{
			t_ray	ray = ray_base;
			double	cur_x_angle = base_x_angle - fov_x / 2 + (float)x / m_data->engine.canvas.width * fov_x;
			cur_x_angle = fmod(cur_x_angle, 2 * M_PI);
			eng_set_transform((t_obj *)&ray, mtx_rotation_x(cur_x_angle));
			double	cur_y_angle = base_y_angle - fov_y / 2 + (float)y / m_data->engine.canvas.height * fov_y;
			cur_y_angle = fmod(cur_y_angle, 2 * M_PI);
			eng_set_transform((t_obj *)&ray, mtx_rotation_y(cur_y_angle));
			ray.direct = mtx_mult_mt(ray.base_obj.transform, ray.direct);
			eng_intersc_ray(&interscs, &ray, (t_obj *) &sph);
			t_intersc	*intersc = eng_ray_hit(&interscs);
			if (intersc)
			{
				////uncomment to get shading
				//t_point	intersc_p = add_t(ray.origin, mult_v(ray.direct, intersc->t));
				//t_vec	rad_v = sub_t(sph.origin, intersc_p);
				//float	dot = dot_prod(norm(rad_v), norm(ray.direct));
				//if (dot < 0)
				{
					//color.full = WHITE;
					//color.argb.r *= -dot;
					//color.argb.g *= -dot;
					//color.argb.b *= -dot;
					pixels[y * m_data->engine.canvas.width + x] = color;
				}
			}
			eng_free_intersc_arr(&interscs);
		}
		printf("y: %lu\n", y);
	}
	//store_as_plain_ppm(m_data, "ENTER FILE NAME TO DOCUMENT PROGRESS.ppm");
}

