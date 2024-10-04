#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

//t_light	eng_randomly_offset_light(t_light in)
//{
//	t_light	out;
//	t_vec	offset;
//
//	out = in;
//	offset = norm(new_vec(1, 0, 0));
//	offset = mtx_mult_mt(mtx_rotation_y(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_rotation_z(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_rotation_x(ft_rand() * M_PI_2), offset);
//	offset = mtx_mult_mt(mtx_scale(in.radius, in.radius, in.radius), offset);
//	out.origin = add_t(out.origin, offset);
//	return (out);
//}

t_light	eng_randomly_offset_light(t_light in)
{
	t_light		out = in;
	double		phi = ft_rand() * 2 * M_PI;
	double 		costheta = ft_rand() * 2 - 1;
	double 		u = ft_rand();
	double		theta = acos(costheta);
	double 		r = in.radius * cbrt(u);

	t_vec offset = new_vec(
		r * sin(theta) * cos(phi),
		r * sin(theta) * sin(phi),
		r * cos(theta)
	);
	out.origin = add_t(out.origin, offset);
	return (out);
}

t_fcolor	eng_shade_hit(t_world world, t_computation comp,
	size_t remaining_reflects)
{
	size_t		i;
	t_fcolor	color;
	t_fcolor	surface;
	bool		in_shadow;
	t_fcolor	reflected;
	t_fcolor	refracted;
	t_light		modified_light;
	double		reflactance;

	color = new_fcolor(0, 0, 0, 0);
	i = 0;
	while (i < world.light_count)
	{
		// modified_light = world.lights[i];//for boolen shadows use this line
		modified_light = eng_randomly_offset_light(world.lights[i]);//for smooth shadows use this line
		in_shadow = eng_is_shadowed(world, comp.over_point, modified_light);
		surface = add_fcolor(color, eng_lighting(comp, modified_light,
					in_shadow));
		reflected = ref_reflected_color(world, comp, remaining_reflects);
		refracted = refracted_color(world, comp, remaining_reflects);
		if (comp.obj->material.reflective > 0 && comp.obj->material.transparency > 0)
		{
			reflactance = ref_schlick(comp);
			reflected = scale_fcolor(reflected, reflactance);
			refracted = scale_fcolor(refracted, 1.0 - reflactance);
		}
		color = add_fcolor(color, surface);
		color = add_fcolor(color, reflected);
		color = add_fcolor(color, refracted);
		i++;
	}
	return (color);
}

t_fcolor	eng_color_at(t_world world, t_ray ray, size_t remaining_reflects)
{
	t_intersc_arr	interscs;
	t_intersc		*hit;
	t_fcolor		color;
	t_computation	comp;

	interscs = eng_new_intersc_arr();
	eng_ray_intersc_world(ray, world, &interscs);
	hit = eng_ray_hit(&interscs);
	if (hit)
	{
		comp = eng_prepare_computation(*hit, ray, interscs);
		color = eng_shade_hit(world, comp, remaining_reflects);
	}
	else
		color = new_fcolor(0, 0, 0, 1);
	eng_free_intersc_arr(&interscs);
	return (color);
}

size_t	eng_put_pixel(t_canvas canvas, size_t x, size_t y, t_fcolor color)
{
	static t_fcolor	mem_sum[HEIGHT][WIDTH];
	static bool		first = true;
	static size_t	iter_count = 0;
	t_fcolor		prev_sum;

	if (first)
	{
		ft_bzero(mem_sum, sizeof mem_sum);
		first = false;
	}
	if (!y && !x)
	{
		iter_count++;
	}
	mem_sum[y][x] = add_fcolor(mem_sum[y][x], color);
	color = div_fcolor(mem_sum[y][x], iter_count);
	((t_uintcolor *)canvas.pixels)[y * canvas.width + x] = fcolor_to_uintcolor(
			color);
	return (iter_count);
}

void	eng_render(t_camera camera, t_world world, t_canvas canvas)
{
	size_t		y;
	size_t		x;
	t_ray		ray;
	t_fcolor	color;
	size_t		iter;

	y = 0;
	while (y < camera.height)
	{
		x = 0;
		while (x < camera.width)
		{
			ray = eng_ray_for_pixel(camera, x, y);
			color = eng_color_at(world, ray, REFLECTION_COUNT);
			iter = eng_put_pixel(canvas, x, y, color);
			x++;
		}
		printf("iter %lu: %f%%\n", iter, ((double)y) / canvas.height * 100);
		y++;
	}
}

t_fcolor	eng_pixel_at(t_canvas canvas, size_t x, size_t y, size_t width)
{
	t_uintcolor	uint;
	t_fcolor	ret;

	ret = new_fcolor(0, 0, 0, 0);
	uint = canvas.pixels[y * width + x];
	ret.a = ((double)uint.argb.a) / 0xFF;
	ret.r = ((double)uint.argb.r) / 0xFF;
	ret.g = ((double)uint.argb.g) / 0xFF;
	ret.b = ((double)uint.argb.b) / 0xFF;
	return (ret);
}
