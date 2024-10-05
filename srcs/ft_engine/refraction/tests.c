#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>

bool	test_prepare_comp_n1_n2(void)
{
	bool			ret = true;
	t_sphere		sph1;
	t_sphere		sph2;
	t_sphere		sph3;
	t_ray			ray;
	t_computation	comp;

	sph1 = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr)&sph1, mtx_scale(2, 2, 2));
	sph1.base_obj.material.refractive_index = 1.5;
	sph2 = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr)&sph2, mtx_translate(0, 0, -0.25));
	sph2.base_obj.material.refractive_index = 2.0;
	sph3 = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr)&sph3, mtx_translate(0, 0, 0.25));
	sph3.base_obj.material.refractive_index = 2.5;
	ray = eng_new_ray(new_point(0, 0, -4), new_vec(0, 0, 1));
	t_intersc		buff[] = {
		{.obj = (t_obj_ptr)&sph1, .t=2},
		{.obj = (t_obj_ptr)&sph2, .t=2.75},
		{.obj = (t_obj_ptr)&sph3, .t=3.25},
		{.obj = (t_obj_ptr)&sph2, .t=4.75},
		{.obj = (t_obj_ptr)&sph3, .t=5.25},
		{.obj = (t_obj_ptr)&sph1, .t=6},
	};
	t_intersc_arr	intersc_arr = eng_new_intersc_arr();
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	double	expect_n1[] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
	double	expect_n2[] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};
	ft_memcpy(intersc_arr.arr, buff, sizeof(buff));
	intersc_arr.count = 6;
	for (int i = 0; i < 6; i++)
	{
		comp = eng_prepare_computation(intersc_arr.arr[i], ray, intersc_arr);
		if (!eq_f(comp.n1, expect_n1[i]))
		{
			printf("%s", FT_ANSI_RED_BOLD);
			ret = false;
			printf("Test failed: eng_prepare_computation: n1 is wrong: %s line %d "
					"iteration %d\nexpected: %lf actual: %lf\n", __FILE__,
					__LINE__, i, expect_n1[i], comp.n1);
			printf("%s", FT_ANSI_RESET);
		}
		//else
		//{
		//	printf("%s", FT_ANSI_GREEN_BOLD);
		//	printf("Test passed: n1 is: %lf\n" "iteration %d\n", comp.n1, i);
		//	printf("%s", FT_ANSI_RESET);
		//}
		if (!eq_f(comp.n2, expect_n2[i]))
		{
			printf("%s", FT_ANSI_RED_BOLD);
			ret = false;
			printf("Test failed: eng_prepare_computation: n2 is wrong: %s line %d "
					"iteration %d\nexpected: %lf actual: %lf\n", __FILE__,
					__LINE__, i, expect_n2[i], comp.n2);
			printf("%s", FT_ANSI_RESET);
		}
		//else
		//{
		//	printf("%s", FT_ANSI_GREEN_BOLD);
		//	printf("Test passed: n2 is: %lf\n" "iteration %d\n", comp.n2, i);
		//	printf("%s", FT_ANSI_RESET);
		//}
	}
	eng_free_intersc_arr(&intersc_arr);
	return (ret);
}

bool	test_prepare_comp_underpoint(void)
{
	bool			ret = true;
	t_ray			ray;
	t_sphere		sph;
	t_intersc		intersc;
	t_intersc		interscs_buff[1];
	t_intersc_arr	interscs;
	t_computation	comp;

	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	sph = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr)&sph, mtx_translate(0, 0, 1));
	intersc.t = 5;
	intersc.obj = (t_obj_ptr)&sph;
	interscs.count = 1;
	interscs.arr = interscs_buff;
	interscs.arr[0] = intersc;
	comp = eng_prepare_computation(intersc, ray, interscs);
	if (comp.under_point.z <= EPSILON / 2)
	{
		ret = false;
		printf("%s", FT_ANSI_RED_BOLD);
		ret = false;
		printf("Test failed: eng_prepare_computation: under_point is wrong: %s line %d"
				"\nexpected >= %lf actual: %lf\n", __FILE__,
				__LINE__, EPSILON / 2, comp.under_point.z);
		printf("%s", FT_ANSI_RESET);
	}
	if (comp.under_point.z <= comp.point.z)
	{
		ret = false;
		printf("%s", FT_ANSI_RED_BOLD);
		ret = false;
		printf("Test failed: eng_prepare_computation: under_point is wrong: %s line %d"
				"\nexpected >= %lf actual: %lf\n", __FILE__,
				__LINE__, comp.point.z, comp.under_point.z);
		printf("%s", FT_ANSI_RESET);
	}
	return (ret);
}

bool	test_refracted_color(void)
{
	bool			ret = true;
	t_world			world = eng_default_world();
	t_obj_ptr		obj = world.objs[0];
	t_ray			ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_intersc_arr	interscs;
	t_intersc		interscs_buffer[2];
	interscs.count = 2;
	interscs.arr = interscs_buffer;
	interscs.arr[0].t = 4;
	interscs.arr[1].t = 6;
	interscs.arr[0].obj = obj;
	interscs.arr[1].obj = obj;
	t_computation comp = eng_prepare_computation(interscs.arr[0], ray, interscs);
	t_fcolor color = refracted_color(world, comp, 5);

	if (!eq_fcolor(color, fcolor_black()))
	{
		printf("%s", FT_ANSI_RED_BOLD);
		ret = false;
		printf("Test failed: refracted_color: %s line %d\n", __FILE__,
				__LINE__);
		print_fcolor("expected", fcolor_black());
		print_fcolor("actual", color);
		printf("%s", FT_ANSI_RESET);
	}
	return (ret);
}

bool	test_refracted_color_total_reflect(void)
{
	bool			ret = true;
	t_world			world = eng_default_world();
	t_obj_ptr		obj = world.objs[0];
	obj->material.transparency = 1;
	obj->material.refractive_index = 1.5;
	t_ray			ray = eng_new_ray(new_point(0, 0, sqrt(2) / 2), new_vec(0, 1, 0));
	t_intersc_arr	interscs;
	t_intersc		interscs_buffer[2];
	interscs.count = 2;
	interscs.arr = interscs_buffer;
	interscs.arr[0].obj = obj;
	interscs.arr[1].obj = obj;
	interscs.arr[0].t = -sqrt(2) / 2;
	interscs.arr[1].t = sqrt(2) / 2;
	t_computation comp = eng_prepare_computation(interscs.arr[1], ray, interscs);
	t_fcolor color = refracted_color(world, comp, 5);

	if (!eq_fcolor(color, fcolor_black()))
	{
		printf("%s", FT_ANSI_RED_BOLD);
		ret = false;
		printf("Test failed: refracted_color: %s line %d\n", __FILE__,
				__LINE__);
		print_fcolor("expected", fcolor_black());
		print_fcolor("actual", color);
		printf("%s", FT_ANSI_RESET);
	}
	return (ret);
}

bool	test_shade_hit_with_transparent_material(void)
{
	bool ret = true;
	t_world world = eng_default_world();

	t_plane floor = eng_new_plane();
	eng_set_transform((t_obj_ptr)&floor, mtx_translate(0, -1, 0));
	floor.base_obj.material.transparency = 0.5;
	floor.base_obj.material.refractive_index = 1.5;
	eng_add_obj_to_world(&world, (t_obj_ptr)&floor);

	t_sphere	ball = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&ball, mtx_translate(0, -3.5, -0.5));
	ball.base_obj.material.fcolor = new_fcolor(1, 0, 0, 1);
	ball.base_obj.material.ambient = 0.5;
	eng_add_obj_to_world(&world, (t_obj_ptr)&ball);

	t_ray ray = eng_new_ray(new_point(0, 0, -3), new_vec(0, -sqrt(2) / 2, sqrt(2) / 2));

	t_intersc_arr xs;
	t_intersc xs_buffer[1] = {{.obj = (t_obj_ptr)&floor, .t = sqrt(2)}};
	xs.count = 1;
	xs.arr = xs_buffer;

	t_computation comps = eng_prepare_computation(xs.arr[0], ray, xs);

	t_fcolor color = eng_shade_hit(world, comps, 5);

	t_fcolor expected = new_fcolor(0.93642, 0.68642, 0.68642, 1);

	if (!eq_fcolor(color, expected))
	{
		printf("%s", FT_ANSI_RED_BOLD);
		ret = false;
		printf("Test failed: shade_hit_with_transparent_material: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected", expected);
		print_fcolor("actual", color);
		printf("%s", FT_ANSI_RESET);
	}
	return ret;
}
