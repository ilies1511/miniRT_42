#include <ft_engine.h>
#include <ft_tuple.h>
#include <libft.h>
#include <ft_floats.h>

bool	test_eng_ray_pos(void)
{
	bool			ret = true;
	t_point			origin;
	t_vec			direct;
	t_ray			ray;
	t_point			expect;
	t_point			actual;

	origin = new_point(2, 3, 4);
	direct = new_vec(1, 0, 0);
	ray = eng_new_ray(origin, direct);
	expect = new_point(2, 3, 4);
	actual = eng_ray_pos(ray, 0);
	if (!eq_t(expect, actual))
	{
		ret = false;
		ft_fprintf(2, "Test fail: eng_ray_pos (%s line %d\n", __FILE__, __LINE__);
	}

	ray = eng_new_ray(origin, direct);
	expect = new_point(3, 3, 4);
	actual = eng_ray_pos(ray, 1);
	if (!eq_t(expect, actual))
	{
		ret = false;
		ft_fprintf(2, "Test fail: eng_ray_pos (%s line %d\n", __FILE__, __LINE__);
	}

	ray = eng_new_ray(origin, direct);
	expect = new_point(1, 3, 4);
	actual = eng_ray_pos(ray, -1);
	if (!eq_t(expect, actual))
	{
		ret = false;
		ft_fprintf(2, "Test fail: eng_ray_pos (%s line %d\n", __FILE__, __LINE__);
	}
	
	ray = eng_new_ray(origin, direct);
	expect = new_point(4.5, 3, 4);
	actual = eng_ray_pos(ray, 2.5);
	if (!eq_t(expect, actual))
	{
		ret = false;
		ft_fprintf(2, "Test fail: eng_ray_pos (%s line %d\n", __FILE__, __LINE__);
	}
	return (ret);
}

bool	test_eng_intersc_ray_sphere(void)
{
	bool		ret = true;

	t_ray		ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_sphere	sph = eng_new_sphere();
	t_intersc_arr	interscs;

	interscs = eng_new_intersc_arr();
	eng_intersc_ray(&interscs, ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 count: %d; actual: %d: %s line %d\n", 2, (int)interscs.count,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 1 && !eq_f(4.0, interscs.arr[0].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", 4.0, interscs.arr[0].t,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 2 && !eq_f(6.0, interscs.arr[1].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", 6.0, interscs.arr[1].t,
			__FILE__, __LINE__);
	}
	for (size_t i = 0; i < interscs.count - 1; i++)
	{
		if (interscs.arr[i].t > interscs.arr[i + 1].t)
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_sphere: \
				 intersct array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	eng_free_intersc_arr(&interscs);

	ray = eng_new_ray(new_point(0, 1, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_intersc_ray(&interscs, ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 count: %d; actual: %d: %s line %d\n", 2, (int)interscs.count,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 1 && !eq_f(5.0, interscs.arr[0].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", 5.0, interscs.arr[0].t,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 2 && !eq_f(5.0, interscs.arr[1].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", 5.0, interscs.arr[1].t,
			__FILE__, __LINE__);
	}
	for (size_t i = 0; i < interscs.count - 1; i++)
	{
		if (interscs.arr[i].t > interscs.arr[i + 1].t)
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_sphere: \
				 intersct array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	eng_free_intersc_arr(&interscs);

	ray = eng_new_ray(new_point(0, 2, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_intersc_ray(&interscs, ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 0)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 count: %d; actual: %d: %s line %d\n", 0, (int)interscs.count,
			__FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);

	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_intersc_ray(&interscs, ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 count: %d; actual: %d: %s line %d\n", 2, (int)interscs.count,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 1 && !eq_f(-1.0, interscs.arr[0].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", -1.0, interscs.arr[0].t,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 2 && !eq_f(1.0, interscs.arr[1].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", 1.0, interscs.arr[1].t,
			__FILE__, __LINE__);
	}
	for (size_t i = 0; i < interscs.count - 1; i++)
	{
		if (interscs.arr[i].t > interscs.arr[i + 1].t)
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_sphere: \
				 intersct array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	eng_free_intersc_arr(&interscs);

	ray = eng_new_ray(new_point(0, 0, 5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_intersc_ray(&interscs, ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 count: %d; actual: %d: %s line %d\n", 2, (int)interscs.count,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 1 && !eq_f(-6.0, interscs.arr[0].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", -6.0, interscs.arr[0].t,
			__FILE__, __LINE__);
	}
	if (interscs.count >= 2 && !eq_f(-4.0, interscs.arr[1].t))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_sphere: expected\
			 intersct: %f; actual: %f: %s line %d\n", -4.0, interscs.arr[1].t,
			__FILE__, __LINE__);
	}
	for (size_t i = 0; i < interscs.count - 1; i++)
	{
		if (interscs.arr[i].t > interscs.arr[i + 1].t)
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_sphere: \
				 intersct array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	eng_free_intersc_arr(&interscs);
	return (ret);
}

bool	test_eng_ray_hit(void)
{
	bool			ret = true;
	t_sphere		sph = eng_new_sphere();
	t_intersc_arr	interscs;
	t_intersc		*actual_hit;
	t_intersc		expected_hit;

	interscs = eng_new_intersc_arr();
	expected_hit = eng_add_intersc(&interscs, (t_obj *)&sph, 1);
	eng_add_intersc(&interscs, (t_obj *)&sph, 2);
	eng_sort_intersc(&interscs);
	actual_hit = eng_ray_hit(&interscs);
	if (actual_hit->t != expected_hit.t || actual_hit->obj != expected_hit.obj)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_hit: %s line %d\n", __FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);

	interscs = eng_new_intersc_arr();
	eng_add_intersc(&interscs, (t_obj *)&sph, -1);
	expected_hit = eng_add_intersc(&interscs, (t_obj *)&sph, 1);
	eng_sort_intersc(&interscs);
	actual_hit = eng_ray_hit(&interscs);
	if (actual_hit->t != expected_hit.t || actual_hit->obj != expected_hit.obj)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_hit: %s line %d\n", __FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);

	interscs = eng_new_intersc_arr();
	eng_add_intersc(&interscs, (t_obj *)&sph, -2);
	eng_add_intersc(&interscs, (t_obj *)&sph, -1);
	eng_sort_intersc(&interscs);
	actual_hit = eng_ray_hit(&interscs);
	if (actual_hit)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_hit: %s line %d\n", __FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);
	interscs = eng_new_intersc_arr();
	eng_add_intersc(&interscs, (t_obj *)&sph, 5);
	eng_add_intersc(&interscs, (t_obj *)&sph, 7);
	eng_add_intersc(&interscs, (t_obj *)&sph, -3);
	expected_hit = eng_add_intersc(&interscs, (t_obj *)&sph, 2);
	eng_sort_intersc(&interscs);
	actual_hit = eng_ray_hit(&interscs);
	if (actual_hit->t != expected_hit.t || actual_hit->obj != expected_hit.obj)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_hit: %s line %d\n", __FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);
	return (ret);
}

bool	test_eng_ray_intersc_world(void)
{
	bool	ret = true;
	t_world	world = eng_default_world();
	t_ray	ray = eng_new_ray(new_point(0, 0, -5),new_vec(0, 0, 1));
	t_intersc_arr	interscs = eng_new_intersc_arr();
	eng_ray_intersc_world(ray, world, &interscs);
	if (interscs.count != 4)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_intersc_world: %s line %d\n",
			__FILE__, __LINE__);
	}
	if (!eq_f(interscs.arr[0].t, 4))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_intersc_world: %s line %d\n",
			__FILE__, __LINE__);
	}	
	if (!eq_f(interscs.arr[1].t, 4.5))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_intersc_world: %s line %d\n",
			__FILE__, __LINE__);
	}
	if (!eq_f(interscs.arr[2].t, 5.5))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_intersc_world: %s line %d\n",
			__FILE__, __LINE__);
	}
	if (!eq_f(interscs.arr[3].t, 6))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_ray_intersc_world: %s line %d\n",
			__FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);
	eng_cleanup_world(&world);
	return (ret);
}
