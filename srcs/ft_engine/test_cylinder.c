#include <main.h>
#include <ft_engine.h>
#include <libft.h>

bool	test_normal_cylinde2(void)
{
	t_cylinder	cylinder;
	t_vec		n;
	t_vec		n2;
	t_vec		n3;
	t_vec		n4;
	t_vec		n5;
	t_vec		n6;
	bool		result;

	cylinder = eng_new_cylinder();
	result = true;
	cylinder.max = 2;
	cylinder.min = 2;
	cylinder.closed = true;
	n = eng_normal_at((t_obj_ptr) & cylinder, new_point(0, 1, 0));
	n2 = eng_normal_at((t_obj_ptr) & cylinder, new_point(0.5, 1, 0));
	n3 = eng_normal_at((t_obj_ptr) & cylinder, new_point(0, 1, 0.5));
	n4 = eng_normal_at((t_obj_ptr) & cylinder, new_point(0, 2, 0));
	n5 = eng_normal_at((t_obj_ptr) & cylinder, new_point(0.5, 2, 0));
	n6  = eng_normal_at((t_obj_ptr) & cylinder, new_point(0, 2, 0.5));
	if (!eq_t(n, new_vec(0, -1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	if (!eq_t(n2, new_vec(0, -1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	if (!eq_t(n3, new_vec(0, -1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	if (!eq_t(n4, new_vec(0, 1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	if (!eq_t(n5, new_vec(0, 1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	if (!eq_t(n6, new_vec(0, 1, 0)))
	{
		printf("normal_cylinder: %s %d\n", __FILE__, __LINE__);
		result = false;
	}
	return (result);
}

bool	test_closed_capped_cylinder(void)
{
	bool		result;
	t_cylinder	cylinder;
	t_ray		ray;
	t_ray		ray2;
	t_ray		ray3;
	t_ray		ray4;
	t_ray		ray5;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;
	t_intersc_arr	intersecs4;
	t_intersc_arr	intersecs5;

	cylinder = eng_new_cylinder();
	result = true;
	cylinder.max = 2;
	cylinder.min = 1;
	cylinder.closed = true;
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	intersecs4 = eng_new_intersc_arr();
	intersecs5 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 3, 0), new_vec(0, -1, 0));
	ray2 = eng_new_ray(new_point(0, 3, -2), new_vec(0, -1, 2));
	ray3 = eng_new_ray(new_point(0, 4, -2), new_vec(0, -1, 1));
	ray4 = eng_new_ray(new_point(0, 0, -2), new_vec(0, 1, 2));
	ray5 = eng_new_ray(new_point(0, -1, -2), new_vec(0, 1, 1));
	ray.direct = norm(ray.direct);
	ray2.direct = norm(ray2.direct);
	ray3.direct = norm(ray3.direct);
	ray4.direct = norm(ray4.direct);
	ray5.direct = norm(ray5.direct);
	eng_intersc_ray_cylinder(&intersecs, ray, &cylinder);
	eng_intersc_ray_cylinder(&intersecs2, ray2, &cylinder);
	eng_intersc_ray_cylinder(&intersecs3, ray3, &cylinder);
	eng_intersc_ray_cylinder(&intersecs4, ray4, &cylinder);
	eng_intersc_ray_cylinder(&intersecs5, ray5, &cylinder);
	if (intersecs.count != 2 || intersecs2.count != 2 || intersecs3.count != 2 ||
		intersecs4.count != 2 || intersecs5.count != 2)
	{
		//printf("TEST: Truncated Cylinder:\nIntersecs.count");
		printf("intersecs.count: %zu\n", intersecs.count);
		printf("intersecs2.count: %zu\n", intersecs2.count);
		printf("intersecs3.count: %zu\n", intersecs3.count);
		printf("intersecs4.count: %zu\n", intersecs4.count);
		printf("intersecs5.count: %zu\n", intersecs5.count);
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	eng_free_intersc_arr(&intersecs);
	eng_free_intersc_arr(&intersecs2);
	eng_free_intersc_arr(&intersecs3);
	eng_free_intersc_arr(&intersecs4);
	eng_free_intersc_arr(&intersecs5);
	return (result);
}

bool	test_capped_cylinder(void)
{
	t_cylinder	cylinder;

	if (cylinder.closed == false)
		return (true);
	else
		return (false);
}

bool	test_truncated_cylinder(void)
{
	t_cylinder		cylinder;
	bool			result;
	t_ray			ray;
	t_ray			ray2;
	t_ray			ray3;
	t_ray			ray4;
	t_ray			ray5;
	t_ray			ray6;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;
	t_intersc_arr	intersecs4;
	t_intersc_arr	intersecs5;
	t_intersc_arr	intersecs6;

	result = true;
	cylinder = eng_new_cylinder();
	cylinder.max = 2;
	cylinder.min = 1;
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	intersecs4 = eng_new_intersc_arr();
	intersecs5 = eng_new_intersc_arr();
	intersecs6 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 1.5, 0), new_vec(0.1, 1, 0));
	ray2 = eng_new_ray(new_point(0, 3, -5), new_vec(0, 0, 1));
	ray3 = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	ray4 = eng_new_ray(new_point(0, 2, -5), new_vec(0, 0, 1));
	ray5 = eng_new_ray(new_point(0, 1, -5), new_vec(0, 0, 1));
	ray6 = eng_new_ray(new_point(0, 1.5, -2), new_vec(0, 0, 1));
	ray.direct = norm(ray.direct);
	ray2.direct = norm(ray2.direct);
	ray3.direct = norm(ray3.direct);
	ray4.direct = norm(ray4.direct);
	ray5.direct = norm(ray5.direct);
	ray6.direct = norm(ray6.direct);
	eng_intersc_ray_cylinder(&intersecs, ray, &cylinder);
	eng_intersc_ray_cylinder(&intersecs2, ray2, &cylinder);
	eng_intersc_ray_cylinder(&intersecs3, ray3, &cylinder);
	eng_intersc_ray_cylinder(&intersecs4, ray4, &cylinder);
	eng_intersc_ray_cylinder(&intersecs5, ray5, &cylinder);
	eng_intersc_ray_cylinder(&intersecs6, ray6, &cylinder);
	if (intersecs.count != 0 || intersecs2.count != 0 || intersecs3.count != 0 ||
		intersecs4.count != 0 || intersecs5.count != 0 || intersecs6.count != 2)
	{
		//printf("TEST: Truncated Cylinder:\nIntersecs.count");
		printf("intersecs.count: %zu\n", intersecs.count);
		printf("intersecs2.count: %zu\n", intersecs2.count);
		printf("intersecs3.count: %zu\n", intersecs3.count);
		printf("intersecs4.count: %zu\n", intersecs4.count);
		printf("intersecs5.count: %zu\n", intersecs5.count);
		printf("intersecs6.count: %zu\n", intersecs6.count);
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	eng_free_intersc_arr(&intersecs);
	eng_free_intersc_arr(&intersecs2);
	eng_free_intersc_arr(&intersecs3);
	eng_free_intersc_arr(&intersecs4);
	eng_free_intersc_arr(&intersecs5);
	eng_free_intersc_arr(&intersecs6);
	return (result);
}

bool	test_normal_at_cylinder(void)
{
	bool			result;
	t_cylinder		cylinder;
	t_vec			vec;
	t_vec			vec2;
	t_vec			vec3;
	t_vec			vec4;

	result = true;
	cylinder = eng_new_cylinder();
	vec = compute_normal_cylinder(&cylinder, new_point(1, 0, 0));
	if (!eq_t(vec, new_vec(1, 0, 0)))
	{
		printf("MINE:\n");
		print_t(2, vec);
		printf("OG:\n");
		print_t(2, new_vec(1, 0, 0));
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	vec2 = compute_normal_cylinder(&cylinder, new_point(0, 5, -1));
	if (!eq_t(vec2, new_vec(0, 0, -1)))
	{
		printf("MINE:\n");
		print_t(2, vec2);
		printf("OG:\n");
		print_t(2, new_vec(0, 0, -1));
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	vec3 = compute_normal_cylinder(&cylinder, new_point(0, -2, 1));
	if (!eq_t(vec3, new_vec(0, 0, 1)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 3 - MINE:\n");
		print_t(2, vec3);
		printf("OG:\n");
		print_t(2, new_vec(0, 0, 1));
		result = false;
	}
	vec4 = compute_normal_cylinder(&cylinder, new_point(-1, 1, 0));
	if (!eq_t(vec4, new_vec(-1, 0, 0)))
	{
		printf("TEST 4 - MINE:\n");
		print_t(2, vec4);
		printf("OG:\n");
		print_t(2, new_vec(-1, 0, 0));
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	return (result);
}

bool	test_cylinder_hits(void)
{
	bool			result;
	t_cylinder		cylinder;
	t_ray			ray;
	t_ray			ray2;
	t_ray			ray3;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;

	result = true;
	cylinder = eng_new_cylinder();
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(1, 0, -5), new_vec(0, 0, 1));
	ray2 = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	ray3 = eng_new_ray(new_point(0.5, 0, -5), new_vec(0.1, 1, 1));
	ray.direct = norm(ray.direct);
	ray2.direct = norm(ray2.direct);
	ray3.direct = norm(ray3.direct);
	eng_intersc_ray(&intersecs, ray, (t_obj_ptr) &cylinder);
	eng_intersc_ray(&intersecs2, ray2, (t_obj_ptr) &cylinder);
	eng_intersc_ray(&intersecs3, ray3, (t_obj_ptr) &cylinder);
	// printf("intersecs.count: %zu\n", intersecs.count);
	// printf("intersecs2.count: %zu\n", intersecs2.count);
	// printf("intersecs3.count: %zu\n", intersecs3.count);
	if ((intersecs.count != 2) || (intersecs2.count != 2) || (intersecs3.count != 2))
	{
		result = false;
		printf("Test failed: ray_intersc_cylinder: %s Line %d\n", __FILE__, __LINE__);
	}
	if ((intersecs.arr[0].t != 5) || (intersecs.arr[1].t != 5))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 1:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", intersecs.arr[0].t, 5.0, \
		intersecs.arr[1].t, 5.0);
		result = false;
	}
	if ((intersecs2.arr[0].t != 4) || (intersecs2.arr[1].t != 6))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 2:\nMY t1: %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs2.arr[0].t, 4.0, intersecs2.arr[1].t, 6.0);
		result = false;
	}
	if ((!eq_f(intersecs3.arr[0].t, 6.80769)) || (!eq_f(intersecs3.arr[1].t, 7.08872)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 3:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs3.arr[0].t, 6.80769, intersecs3.arr[1].t, 7.08872);
		result = false;
	}
	// printf("RAY1 Intersecs Count: %d\nRAY2 Intersecs Count: %d\nRAY3 Intersecs Count: %d\n", \
	// 		intersecs.count, intersecs2.count, intersecs3.count);
	// eng_free_intersc_arr(&intersecs);
	// eng_free_intersc_arr(&intersecs2);
	// eng_free_intersc_arr(&intersecs3);
	return (result);
}

bool	test_cylinder_no_hits(void)
{
	bool			result;
	t_cylinder		cylinder;
	t_ray			ray;
	t_ray			ray2;
	t_ray			ray3;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;

	result = true;
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(1, 0, 0), new_vec(0, 1, 0));
	ray2 = eng_new_ray(new_point(0, 0, 0), new_vec(0, 1, 0));
	ray3 = eng_new_ray(new_point(0, 0, -5), new_vec(1, 1, 1));
	cylinder = eng_new_cylinder();
	ray.direct = norm(ray.direct);
	ray2.direct = norm(ray2.direct);
	ray3.direct = norm(ray3.direct);
	eng_intersc_ray_cylinder(&intersecs, ray, &cylinder);
	eng_intersc_ray_cylinder(&intersecs2, ray2, &cylinder);
	eng_intersc_ray_cylinder(&intersecs3, ray3, &cylinder);
	eng_sort_intersc(&intersecs);
	eng_sort_intersc(&intersecs2);
	eng_sort_intersc(&intersecs3);
	if (intersecs.count != 0 || intersecs2.count != 0 || intersecs3.count != 0)
	{
		printf("%s Line: %d", __FILE__, __LINE__);
		printf("intersecs.count should be 0\n");
		printf("RAY1 Intersecs Count: %lu\nRAY2 Intersecs Count: %lu\nRAY3 Intersecs Count: %lu\n", \
			intersecs.count, intersecs2.count, intersecs3.count);
		result = false;
	}
	eng_free_intersc_arr(&intersecs);
	eng_free_intersc_arr(&intersecs2);
	eng_free_intersc_arr(&intersecs3);
	return (result);
}
