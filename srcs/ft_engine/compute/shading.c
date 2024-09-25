#include <ft_engine.h>
#include <libft.h>

t_fcolor	eng_shade_hit(t_world world, t_computation comp)
{
	size_t		i;
	t_fcolor	color;
	bool		in_shadow;

	color = new_fcolor(0, 0, 0, 0);
	i = 0;
	while (i < world.light_count)
	{
		in_shadow = false;
		if (eng_is_shadowed(world, comp.over_point))
			in_shadow = true;
		color = add_fcolor(color, eng_lighting_impr(comp.obj->material,
			world.lights[i], comp.over_point, comp.eye_v, comp.normal_v, in_shadow));
		i++;
	}
	return (color);
}

t_fcolor	eng_color_at(t_world world, t_ray ray)
{
	t_intersc_arr	interscs;
	t_intersc		*intersc;
	t_fcolor		color;
	t_computation	comp;

	interscs = eng_new_intersc_arr();
	eng_ray_intersc_world(ray, world, &interscs);
	intersc = eng_ray_hit(&interscs);
	if (intersc)
	{
		comp = eng_prepare_computation(*intersc, ray);
		color = eng_shade_hit(world, comp);
	}
	else
		color = new_fcolor(0, 0, 0, 1);
	eng_free_intersc_arr(&interscs);
	return (color);
}

bool	test_shading_outside_intersection(void)
{
	bool		ret = true;
	t_world		w = eng_default_world();
	t_ray		r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_obj		*shape = w.objs[0];
	t_intersc	i = {4, shape};

	t_computation comps = eng_prepare_computation(i, r);
	t_fcolor c = eng_shade_hit(w, comps);
	t_fcolor expected = new_fcolor(0.38066, 0.47583, 0.2855, 1);
	if (!eq_fcolor(c, expected))
	{
		ft_fprintf(2, "test failed: eng_shade_hit: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", c);
		ret = false;
	}
	eng_cleanup_world(&w);

	w = eng_default_world();
	w.lights[0].intensity = new_fcolor(1, 1, 1, 1);
	w.lights[0].origin = new_point(0, 0.25, 0);

	r = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	shape = w.objs[1];
	i.t = 0.5;
	i.obj = shape;
	comps = eng_prepare_computation(i, r);
	c = eng_shade_hit(w, comps);
	expected = new_fcolor(0.90498, 0.90498, 0.90498, 1);
	if (!eq_fcolor(c, expected))
	{
		ft_fprintf(2, "test failed: eng_shade_hit: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", c);
		ret = false;
	}
	eng_cleanup_world(&w);
	return (ret);
}

bool	test_eng_color_at(void)
{
	bool		ret = true;
	t_world		w = eng_default_world();
	t_ray		r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 1, 0));
	t_fcolor	c = eng_color_at(w, r);
	t_fcolor	expected_color = new_fcolor(0.0f, 0.0f, 0.0f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}
	eng_cleanup_world(&w);

	w = eng_default_world();
	r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	c = eng_color_at(w, r);
	expected_color = new_fcolor(0.38066f, 0.47583f, 0.2855f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}
	eng_cleanup_world(&w);

    w = eng_default_world();
    t_obj	*outer = w.objs[0];
    outer->material.ambient = 1.0f;
    t_obj	*inner = w.objs[1];
    inner->material.ambient = 1.0f;
    r = eng_new_ray(new_point(0, 0, 0.75f), new_vec(0, 0, -1));
    c = eng_color_at(w, r);
	if (!eq_fcolor(c, inner->material.fcolor))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}
	eng_cleanup_world(&w);

	return (ret);
}

void	eng_put_pixel(t_canvas canvas, size_t x, size_t y, t_fcolor color)
{
	((t_uintcolor *)canvas.pixels)[y * canvas.width + x] = fcolor_to_uintcolor(color);
}


void	eng_render(t_camera camera, t_world world, t_canvas canvas)
{
	for (size_t y = 0; y < camera.height; y++)
	{
		for (size_t x = 0; x < camera.width; x++)
		{
			t_ray	ray = eng_ray_for_pixel(camera, x, y);
			t_fcolor color = eng_color_at(world, ray);
			eng_put_pixel(canvas, x, y, color);
		}
		printf("%f%%\n", ((float)y) / canvas.height * 100);
	}
}

t_fcolor	eng_pixel_at(t_canvas canvas, size_t x, size_t y, size_t width)
{
	t_uintcolor	uint;
	t_fcolor	ret;

	ret = new_fcolor(0, 0, 0, 0);
	uint = canvas.pixels[y * width + x];
	ret.a = ((float)uint.argb.a) / 0xFF;
	ret.r = ((float)uint.argb.r) / 0xFF;
	ret.g = ((float)uint.argb.g) / 0xFF;
	ret.b = ((float)uint.argb.b) / 0xFF;
	return (ret);
}

bool	test_eng_render(void)
{
	bool	ret = true;
	mlx_t *mlx = mlx_init(11, 11, "TEST CASE", false);
	mlx_image_t	*img = mlx_new_image(mlx, 11, 11);
	t_world		world = eng_default_world();

	t_canvas		canvas = {
		.width = 11,
		.height = 11,
		.pixels = (t_uintcolor *)img->pixels
	};

	eng_render(
		eng_new_camera(11, 11, M_PI_2), world, canvas);
	if (eq_fcolor(eng_pixel_at(canvas, 5, 5, 11), new_fcolor(0.38066, 0.47583, 0.2855, 1)))
	{
		ret = false;
		printf("test failed %s line %d\n", __FILE__, __LINE__);
	}
	mlx_delete_image(mlx, img);
	mlx_close_window(mlx);
	eng_cleanup_world(&world);
	return (ret);
}
