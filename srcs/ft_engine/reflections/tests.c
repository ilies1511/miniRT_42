#include <ft_engine.h>
#include <ft_reflection.h>
#include <main.h>
#include <ft_matrix.h>

bool	test_eng_reflect(void)
{
	bool	ret = true;
	t_vec	vec;
	t_vec	normal;
	t_vec	expect;
	t_vec	actual;

	vec = new_vec(1, -1, 0);
	normal = new_vec(0, 1, 0);
	expect = new_vec(1, 1, 0);
	actual = ref_reflect(vec, normal);
	if (!eq_t(expect, actual))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_refelct: %s line %d\n", __FILE__, __LINE__);
		print_t(2, actual);
	}
	vec = new_vec(0, -1, 0);
	normal = new_vec(sqrt(2)/2, sqrt(2)/2, 0);
	expect = new_vec(1, 0, 0);
	actual = ref_reflect(vec, normal);
	if (!eq_t(expect, actual))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_reflect: %s line %d\n", __FILE__, __LINE__);
		print_t(2, actual);
	}
	return (ret);
}

bool	test_ref_reflect_color_none(void)
{
	bool			ret = true;
	t_world			world;
	t_obj_ptr		obj;
	t_ray			ray;
	t_intersc		intersc;
	t_computation	comp;
	t_fcolor		actual;
	t_fcolor		expect;
	t_intersc_arr	interscs = eng_new_intersc_arr();
	dyn_arr_resize((void **)&interscs.arr);
	interscs.count = 1;

	world = eng_default_world();
	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	obj = world.objs[1];
	obj->material.ambient = 1;
	intersc.t = 1;
	intersc.obj = obj;
	interscs.arr[0] = intersc;
	comp = eng_prepare_computation(intersc, ray, interscs);
	expect = fcolor_black();
	actual = ref_reflected_color(world, comp, 10);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: ref_reflected_color reflects when it shouldn't: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	eng_free_intersc_arr(&interscs);
	return (ret);
}

bool	test_ref_reflect_color(void)
{
	bool			ret = true;
	t_world			world;
	t_plane			plane;
	t_ray			ray;
	t_intersc		intersc;
	t_computation	comp;
	t_fcolor		actual;
	t_fcolor		expect;
	t_obj_ptr		obj;
	t_intersc_arr	interscs = eng_new_intersc_arr();
	dyn_arr_resize((void **)&interscs.arr);
	interscs.count = 1;

	world = eng_default_world();
	plane = eng_new_plane();
	plane.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj_ptr)&plane, mtx_translate(0, -1, 0));
	eng_add_obj_to_world(&world, (t_obj_ptr)&plane);
	obj = world.objs[world.obj_count - 1];
	ray = eng_new_ray(new_point(0, 0, -3), new_vec(0, -sqrt(2) / 2, sqrt(2) / 2));

	intersc.t = sqrt(2);
	intersc.obj = obj;
	interscs.arr[0] = intersc;
	comp = eng_prepare_computation(intersc, ray, interscs);
	expect = new_fcolor(0.19032, 0.2379, 0.14274, 1);
	actual = ref_reflected_color(world, comp, 10);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: ref_reflected_color: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	return (ret);
}

bool	test_ref_with_shade_hit(void)
{
	bool			ret = true;
	t_world			world;
	t_plane			plane;
	t_ray			ray;
	t_intersc		intersc;
	t_computation	comp;
	t_fcolor		actual;
	t_fcolor		expect;
	t_obj_ptr		obj;
	t_intersc_arr	interscs = eng_new_intersc_arr();
	dyn_arr_resize((void **)&interscs.arr);
	interscs.count = 1;

	world = eng_default_world();
	plane = eng_new_plane();
	plane.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj_ptr)&plane, mtx_translate(0, -1, 0));
	eng_add_obj_to_world(&world, (t_obj_ptr)&plane);
	obj = world.objs[world.obj_count - 1];
	ray = eng_new_ray(new_point(0, 0, -3), new_vec(0, -sqrt(2) / 2, sqrt(2) / 2));

	intersc.t = sqrt(2);
	intersc.obj = obj;
	interscs.arr[0] = intersc;
	comp = eng_prepare_computation(intersc, ray, interscs);
	expect = new_fcolor(0.87677, 0.92436, 0.82918, 1);
	actual = eng_shade_hit(world, comp, 10);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: ref_reflected_color: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}

	eng_free_intersc_arr(&interscs);
	return (ret);
}

bool	test_ref_infinite_recursion(void)
{
	bool			ret = true;
	t_world			world;
	t_light			light;
	t_plane			lower;
	t_plane			upper;
	t_ray			ray;

	world = eng_new_world();
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, 0));
	eng_add_obj_to_world(&world, (t_obj_ptr)&light);
	lower = eng_new_plane();
	lower.base_obj.material.reflective = 1.0;
	eng_set_transform((t_obj_ptr)&lower, mtx_translate(0, -1, 0));
	eng_add_obj_to_world(&world, (t_obj_ptr)&lower);
	upper = eng_new_plane();
	upper.base_obj.material.reflective = 1.0;
	eng_set_transform((t_obj_ptr)&upper, mtx_translate(0, 1, 0));
	eng_add_obj_to_world(&world, (t_obj_ptr)&upper);
	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 1, 0));
	printf("testing for infinit recursion, crashes on error..\n");
	eng_color_at(world, ray, 10);
	printf("passed infinit recursion test\n");

	return (ret);
}
