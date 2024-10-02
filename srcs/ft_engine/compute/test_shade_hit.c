#include <ft_engine.h>
#include <libft.h>
#include <main.h>

bool	test_shade_hit(void)
{
	t_world			w;
	t_light			light;
	t_sphere		s;
	t_sphere		s2;
	t_ray			ray;
	t_intersc		intersec;
	t_intersc_arr	intersecs;
	t_computation	comp;
	t_fcolor		soll_color;
	t_fcolor		ist_color;
	bool			status;

	soll_color = new_fcolor(0.1, 0.1, 0.1, 1);
	w = eng_new_world();
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	eng_add_obj_to_world(&w, (t_obj *)&light);
	s = eng_new_sphere();
	eng_add_obj_to_world(&w, (t_obj *)&s);
	s2 = eng_new_sphere();
	eng_set_transform((t_obj *)&s2, mtx_translate(0, 0, 10));
	eng_add_obj_to_world(&w, (t_obj *)&s2);
	intersecs = eng_new_intersc_arr();
	intersec = eng_add_intersc(&intersecs, (t_obj *)&s2, 4);
	ray = eng_new_ray(new_point(0, 0, 5), new_vec(0, 0, 1));
	eng_intersc_ray(&intersecs, ray, (t_obj *)&s2);
	comp = eng_prepare_computation(intersec, ray);
	ist_color = eng_shade_hit(w, comp, 10);
	if (eq_fcolor(ist_color, soll_color))
		status = true;
	else
	{
		print_fcolor("SOLL:\n", soll_color);
		print_fcolor("\nIST:\n", ist_color);
		status = false;
	}
	return (eng_free_intersc_arr(&intersecs), status);
}

bool	test_eng_color_at(void)
{
	bool		ret = true;
	t_world		w = eng_default_world();
	t_ray		r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 1, 0));
	t_fcolor	c = eng_color_at(w, r, 10);
	t_fcolor	expected_color = new_fcolor(0.0f, 0.0f, 0.0f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}

	w = eng_default_world();
	r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	c = eng_color_at(w, r, 10);
	expected_color = new_fcolor(0.38066f, 0.47583f, 0.2855f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}

    w = eng_default_world();
    t_obj	*outer = w.objs[0];
    outer->material.ambient = 1.0f;
    t_obj	*inner = w.objs[1];
    inner->material.ambient = 1.0f;
    r = eng_new_ray(new_point(0, 0, 0.75f), new_vec(0, 0, -1));
    c = eng_color_at(w, r, 10);
	if (!eq_fcolor(c, inner->material.fcolor))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}
	return (ret);
}

bool	test_shading_outside_intersection(void)
{
	bool		ret = true;
	t_world		w = eng_default_world();
	t_ray		r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_obj		*shape = w.objs[0];
	t_intersc	i = {4, shape};

	t_computation comps = eng_prepare_computation(i, r);
	t_fcolor c = eng_shade_hit(w, comps, 10);
	t_fcolor expected = new_fcolor(0.38066, 0.47583, 0.2855, 1);
	if (!eq_fcolor(c, expected))
	{
		ft_fprintf(2, "test failed: eng_shade_hit: %s line %d\n", __FILE__,
			__LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", c);
		ret = false;
	}
	w = eng_default_world();
	w.lights[0].intensity = new_fcolor(1, 1, 1, 1);
	w.lights[0].origin = new_point(0, 0.25, 0);
	r = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	shape = w.objs[1];
	i.t = 0.5;
	i.obj = shape;
	comps = eng_prepare_computation(i, r);
	c = eng_shade_hit(w, comps, 10);
	expected = new_fcolor(0.90498, 0.90498, 0.90498, 1);
	if (!eq_fcolor(c, expected))
	{
		ft_fprintf(2, "test failed: eng_shade_hit: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", c);
		ret = false;
	}
	return (ret);
}

bool	test_eng_render(void)
{
	bool	ret = true;
	t_world		world = eng_default_world();
	mlx_t *mlx = mlx_init(11, 11, "TEST CASE", false);
	mlx_image_t	*img = mlx_new_image(mlx, 11, 11);

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

//==40235==    still reachable: 309,526 bytes in 3,127 blocks
//mlx leak deteteced by valgrind, is in all mlx projects i checked on github
	mlx_delete_image(mlx, img);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	return (ret);
}
