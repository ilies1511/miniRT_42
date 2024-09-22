#include <ft_engine.h>
#include <libft.h>

t_fcolor	eng_shade_hit(t_world world, t_computation comp)
{
	size_t		i;
	t_fcolor	color;

	color = new_fcolor(0, 0, 0, 0);
	i = 0;
	while (i < world.light_count)
	{
		color = add_fcolor(color, eng_lighting(comp.obj->material,
			world.lights[i], comp.point, comp.eye_v, comp.normal_v));
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
	bool	ret = true;
	t_world w = eng_default_world();
	t_ray r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_obj *shape = w.objs[0];
	t_intersc i = {4, shape};

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
	cleanup_world(&w);

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
	cleanup_world(&w);
	return (ret);
}

bool	test_eng_color_at(void)
{
	bool	ret = true;
	t_world w = eng_default_world();
	t_ray r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 1, 0));
	t_fcolor c = eng_color_at(w, r);
	t_fcolor expected_color = new_fcolor(0.0f, 0.0f, 0.0f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}

	w = eng_default_world();
	r = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	c = eng_color_at(w, r);
	expected_color = new_fcolor(0.38066f, 0.47583f, 0.2855f, 0.0f);
	if (!eq_fcolor(c, expected_color))
	{
		ft_fprintf(2, "test failed: eng_color_at: %s line %d\n", __FILE__, __LINE__);
		ret = false;
	}
	return (ret);
}
