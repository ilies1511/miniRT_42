#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

//t_light	adjust_light(t_light in)
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

#ifdef SMOOTH_SHADOWS

static t_light	adjust_light(t_light light)
{
	double	phi;
	double	costheta;
	double	theta;
	double	r;
	t_vec	offset;

	phi = ft_rand() * 2 * M_PI;
	costheta = ft_rand() * 2 - 1;
	theta = acos(costheta);
	r = light.radius * cbrt(ft_rand());
	offset = new_vec(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi),
			r * cos(theta));
	light.origin = add_t(light.origin, offset);
	return (light);
}
#elif HARD_SHADOWS

static t_light	adjust_light(t_light light)
{
	return (light);
}
#else

t_light	adjust_light(t_light in)
{
	ft_assert(0, __FILE__,
		__LINE__, "neither SMOOTH_SHADOWS nor HARD_SHADOWS defined");
	__builtin_unreachable();
}
#endif // SOFT_SHADOWS HARD_SHADWOS

static inline bool	in_light_fov(t_light light, t_point point)
{
	t_vec	ray_direct;
	double	cosine;

	if (light.type == POINT_LIGHT)
		return (true);
	if (eq_t(light.origin, point))
		return (true);
	ray_direct = norm(sub_t(light.origin, point));
	cosine = dot_prod(ray_direct, light.direct);
	if (fabs(cosine) > light.cosine_range)
		return (true);
	return (false);
}

t_fcolor	eng_ambient42(t_world world, t_fcolor color_at)
{
	return (mult_fcolor(world.ambient42, color_at));
}

static void calculate_color(t_shade_hit_norm *n)
{
	n->color = add_fcolor(n->color, n->surface);
	n->color = add_fcolor(n->color, n->reflected);
	n->color = add_fcolor(n->color, n->refracted);
}

t_fcolor	eng_shade_hit(t_world world, t_computation comp, \
	size_t remaining_reflects)
{
	t_shade_hit_norm	n;

	n.color = fcolor_black();
	n.i = -1;
	while (++n.i < (int)world.light_count)
	{
		n.light = adjust_light(world.lights[n.i]);
		if (!in_light_fov(n.light, comp.point))
			n.in_shadow = true;
		else
			n.in_shadow = eng_is_shadowed(world, comp.over_point, n.light);
		n.surface = eng_lighting(comp, n.light, n.in_shadow);
		n.reflected = ref_reflected_color(world, comp, remaining_reflects);
		n.refracted = refracted_color(world, comp, remaining_reflects);
		if (comp.obj->material.reflective > 0 \
				&& comp.obj->material.transparency > 0)
		{
			n.reflactance = ref_schlick(comp);
			n.reflected = scale_fcolor(n.reflected, n.reflactance);
			n.refracted = scale_fcolor(n.refracted, 1.0 - n.reflactance);
		}
		calculate_color(&n);
	}
	return (n.color);
}

t_fcolor	eng_shade_hit42(t_world world, t_computation comp, \
	size_t remaining_reflects)
{
	t_shade_hit_norm	n;

	n.color = eng_ambient42(world, comp.color_at);
	n.i = -1;
	while (++n.i < (int)world.light_count)
	{
		n.light = adjust_light(world.lights[n.i]);
		if (in_light_fov(n.light, comp.point) && !eng_is_shadowed(world, \
			comp.over_point, n.light))
			n.surface = eng_lighting42(comp, n.light);
		else
			n.surface = fcolor_black();
		n.reflected = ref_reflected_color(world, comp, remaining_reflects);
		n.refracted = refracted_color(world, comp, remaining_reflects);
		if (comp.obj->material.reflective > 0 \
			&& comp.obj->material.transparency > 0)
		{
			n.reflactance = ref_schlick(comp);
			n.reflected = scale_fcolor(n.reflected, n.reflactance);
			n.refracted = scale_fcolor(n.refracted, 1.0 - n.reflactance);
		}
		calculate_color(&n);
	}
	return (n.color);
}

//if this ifdef block is moved the 'test' rule in the make file needs
//to be changed accordingly
#ifdef AMBIENT_CUSTOM

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
#elif AMBIENT_42

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
		color = eng_shade_hit42(world, comp, remaining_reflects);
	}
	else
		color = new_fcolor(0, 0, 0, 1);
	eng_free_intersc_arr(&interscs);
	return (color);
}

#else

# error "ambient macro not defined!"

#endif //AMBIENT

size_t	eng_put_pixel(t_canvas canvas, size_t x, size_t y, t_fcolor color)
{
	static t_fcolor	mem_sum[HEIGHT][WIDTH];
	static bool		first = true;
	static size_t	iter_count = 0;

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
