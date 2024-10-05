#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

#define SMOOTH_SHADOWS
#define TEST
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

t_fcolor	eng_shade_hit(t_world world, t_computation comp,
	size_t remaining_reflects)
{
	int			i;
	t_fcolor	color;
	t_fcolor	surface;
	bool		in_shadow;
	t_fcolor	reflected;
	t_fcolor	refracted;
	t_light		light;
	double		reflactance;

	color = fcolor_black();
	i = -1;
	while (++i < (int)world.light_count)
	{
		light = adjust_light(world.lights[i]);
		if (!in_light_fov(light, comp.point))
			in_shadow = true;
		else
			in_shadow = eng_is_shadowed(world, comp.over_point, light);
		surface = eng_lighting(comp, light, in_shadow);
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
	}
	return (color);
}

t_fcolor	eng_shade_hit42(t_world world, t_computation comp,
	size_t remaining_reflects)
{
	int			i;
	t_fcolor	color;
	t_fcolor	surface;
	t_fcolor	reflected;
	t_fcolor	refracted;
	t_light		light;
	double		reflactance;

	world.ambient42 = scale_fcolor(new_fcolor(1, 1, 1, 1), 0.2);//TODO: this has to come from parser
	color = eng_ambient42(world, comp.color_at);
	i = -1;
	while (++i < (int)world.light_count)
	{
		light = adjust_light(world.lights[i]);
		if (in_light_fov(light, comp.point) && !eng_is_shadowed(world, comp.over_point, light))
			surface = eng_lighting42(comp, light);
		else
			surface = fcolor_black();
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
	}
	return (color);
}

//if this ifdef block is moved the 'test' rule in the make file needs
//to be changed accordingly
#ifdef TEST

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
#else

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
#endif //TEST

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
