#include <ft_engine.h>
#include <libft.h>
#include <ft_reflection.h>

t_fcolor	eng_shade_hit(t_world world, t_computation comp,
	size_t remaining_reflects)
{
	size_t		i;
	t_fcolor	color;
	bool		in_shadow;
	t_fcolor	reflected;

	color = new_fcolor(0, 0, 0, 0);
	i = 0;
	while (i < world.light_count)
	{
		in_shadow = false;
		if (eng_is_shadowed(world, comp.over_point))
			in_shadow = true;
		color = add_fcolor(color, eng_lighting(comp, world.lights[i],
					in_shadow));
		reflected = ref_reflected_color(world, comp, remaining_reflects);
		color = add_fcolor(color, reflected);
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

void	eng_put_pixel(t_canvas canvas, size_t x, size_t y, t_fcolor color)
{
	((t_uintcolor *)canvas.pixels)[y * canvas.width + x] = fcolor_to_uintcolor(
			color);
}

void	eng_render(t_camera camera, t_world world, t_canvas canvas)
{
	size_t		y;
	size_t		x;
	t_ray		ray;
	t_fcolor	color;

	y = 0;
	while (y < camera.height)
	{
		x = 0;
		while (x < camera.width)
		{
			ray = eng_ray_for_pixel(camera, x, y);
			color = eng_color_at(world, ray, REFLECTION_COUNT);
			eng_put_pixel(canvas, x, y, color);
			x++;
		}
		printf("%f%%\n", ((double)y) / canvas.height * 100);
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
