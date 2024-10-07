#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <ft_reflection.h>
#include <ft_refraction.h>

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
	// printf("render\n");
	while (y < camera.height)
	{
		x = 0;
		// printf("row\n");
		while (x < camera.width)
		{
			// printf("pixel\n");
			ray = eng_ray_for_pixel(camera, x, y);
			color = eng_color_at(world, ray, REFLECTION_COUNT);
			iter = eng_put_pixel(canvas, x, y, color);
			x++;
		}
		printf("iter %lu: %f%%\n", iter, ((double)y) / canvas.height * 100);
		y++;
	}
}
