#include <ft_engine.h>
#include <ft_tuple.h>
#include <libft.h>
#include <ft_floats.h>

bool	test_eng_ray_pos(void)
{
	bool	ret = true;
	t_point	origin;
	t_vec	direct;
	t_ray	ray;
	t_point	expect;
	t_point	actual;

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

bool	test_eng_intersects_ray_sphere(void)
{
	bool		ret = true;
	t_ray		ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_sphere	sph = eng_new_sphere();
	float		*intersects = NULL;
	int			intersect_count;

	intersect_count = eng_intersects_ray_sphere(ray, sph, &intersects);
	if (intersect_count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 count: %d; actual: %d: %s line %d\n", 2, intersect_count,
			__FILE__, __LINE__);
	}
	if (intersect_count >= 1 && !eq_f(4.0, intersects[0]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", 4.0, intersects[0],
			__FILE__, __LINE__);
	}
	if (intersect_count >= 2 && !eq_f(6.0, intersects[1]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", 6.0, intersects[1],
			__FILE__, __LINE__);
	}
	for (int i = 0; i < intersect_count - 1; i++)
	{
		if (intersects[i] > intersects[i + 1])
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_spered: \
				 intersect array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	dyn_arr_free((void **)(&intersects));

	ray = eng_new_ray(new_point(0, 1, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersect_count = eng_intersects_ray_sphere(ray, sph, &intersects);
	if (intersect_count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 count: %d; actual: %d: %s line %d\n", 2, intersect_count,
			__FILE__, __LINE__);
	}
	if (intersect_count >= 1 && !eq_f(5.0, intersects[0]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", 5.0, intersects[0],
			__FILE__, __LINE__);
	}
	if (intersect_count >= 2 && !eq_f(5.0, intersects[1]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", 5.0, intersects[1],
			__FILE__, __LINE__);
	}
	for (int i = 0; i < intersect_count - 1; i++)
	{
		if (intersects[i] > intersects[i + 1])
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_spered: \
				 intersect array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	dyn_arr_free((void **)(&intersects));

	ray = eng_new_ray(new_point(0, 2, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersect_count = eng_intersects_ray_sphere(ray, sph, &intersects);
	if (intersect_count != 0)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 count: %d; actual: %d: %s line %d\n", 0, intersect_count,
			__FILE__, __LINE__);
	}
	dyn_arr_free((void **)(&intersects));

	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersect_count = eng_intersects_ray_sphere(ray, sph, &intersects);
	if (intersect_count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 count: %d; actual: %d: %s line %d\n", 2, intersect_count,
			__FILE__, __LINE__);
	}
	if (intersect_count >= 1 && !eq_f(-1.0, intersects[0]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", -1.0, intersects[0],
			__FILE__, __LINE__);
	}
	if (intersect_count >= 2 && !eq_f(1.0, intersects[1]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", 1.0, intersects[1],
			__FILE__, __LINE__);
	}
	for (int i = 0; i < intersect_count - 1; i++)
	{
		if (intersects[i] > intersects[i + 1])
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_spered: \
				 intersect array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	dyn_arr_free((void **)(&intersects));

	ray = eng_new_ray(new_point(0, 0, 5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersect_count = eng_intersects_ray_sphere(ray, sph, &intersects);
	if (intersect_count != 2)
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 count: %d; actual: %d: %s line %d\n", 2, intersect_count,
			__FILE__, __LINE__);
	}
	if (intersect_count >= 1 && !eq_f(-6.0, intersects[0]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", -6.0, intersects[0],
			__FILE__, __LINE__);
	}
	if (intersect_count >= 2 && !eq_f(-4.0, intersects[1]))
	{
		ret = false;
		fprintf(stderr, "test failed: eng_interscts_ray_spered: expected\
			 intersect: %f; actual: %f: %s line %d\n", -4.0, intersects[1],
			__FILE__, __LINE__);
	}
	for (int i = 0; i < intersect_count - 1; i++)
	{
		if (intersects[i] > intersects[i + 1])
		{
			ret = false;
			fprintf(stderr, "test failed: eng_interscts_ray_spered: \
				 intersect array is not sorted: %s line %d\n",
				__FILE__, __LINE__);
		}
	}
	dyn_arr_free((void **)(&intersects));
	return (ret);
}
