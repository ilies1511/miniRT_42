#include <main.h>
#include <ft_engine.h>
#include <libft.h>

bool	test_normal_at_cylinder(void)
{
	bool			result;
	t_cylinder		cylinder;
	t_vec			vec;
	t_vec			vec2;
	t_vec			vec3;
	t_vec			vec4;

	result = true;
	vec = compute_normal_cylinder(new_point(1, 0, 0));
	if (!eq_t(vec, new_vec(1, 0, 0)))
	{
		printf("MINE:\n");
		print_t(2, vec);
		printf("OG:\n");
		print_t(2, new_vec(1, 0, 0));
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	vec2 = compute_normal_cylinder(new_point(0, 5, -1));
	if (!eq_t(vec2, new_vec(0, 0, -1)))
	{
		printf("MINE:\n");
		print_t(2, vec2);
		printf("OG:\n");
		print_t(2, new_vec(0, 0, -1));
		printf("%s Line %d\n", __FILE__, __LINE__);
		result = false;
	}
	vec3 = compute_normal_cylinder(new_point(0, -2, 1));
	if (!eq_t(vec3, new_vec(0, 0, 1)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 3 - MINE:\n");
		print_t(2, vec3);
		printf("OG:\n");
		print_t(2, new_vec(0, 0, 1));
		result = false;
	}
	vec4 = compute_normal_cylinder(new_point(-1, 1, 0));
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
	t_vec			direction;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;

	result = true;
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(1, 0, -5), new_vec(0, 0, 1));
	ray2 = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	ray3 = eng_new_ray(new_point(0.5, 0, -5), new_vec(0.1, 1, 1));
	cylinder = eng_new_cylinder();
	ray.direct = norm(ray.direct);
	ray2.direct = norm(ray2.direct);
	ray3.direct = norm(ray3.direct);
	eng_intersc_ray_cylinder(&intersecs, ray, &cylinder);
	eng_intersc_ray_cylinder(&intersecs2, ray2, &cylinder);
	eng_intersc_ray_cylinder(&intersecs3, ray3, &cylinder);

	if ((intersecs.count != 2) || (intersecs2.count != 2) || (intersecs3.count != 2))
		return (false);
	if ((intersecs.arr[0].t != 5) || (intersecs.arr[1].t != 5))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		return (printf("TEST 1:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", intersecs.arr[0].t, 5, \
		intersecs.arr[1].t), 5, false);
	}
	if ((intersecs2.arr[0].t != 4) || (intersecs2.arr[1].t != 6))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		return (printf("TEST 2:\nMY t1: %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs2.arr[0].t, 4, intersecs2.arr[1].t, 6), false);
	}
	if ((!eq_f(intersecs3.arr[0].t, 6.80769)) || (!eq_f(intersecs3.arr[1].t, 7.08872)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		return (printf("TEST 3:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs3.arr[0].t, 6.80769, intersecs3.arr[1].t, 7.08872), false);
	}
	printf("RAY1 Intersecs Count: %d\nRAY2 Intersecs Count: %d\nRAY3 Intersecs Count: %d\n", \
			intersecs.count, intersecs2.count, intersecs3.count);
	return (result);
}

bool	test_cylinder_no_hits(void)
{
	bool			result;
	t_cylinder		cylinder;
	t_ray			ray;
	t_ray			ray2;
	t_ray			ray3;
	t_vec			direction;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;

	result = false;
	intersecs = eng_new_intersc_arr();
	intersecs2 = eng_new_intersc_arr();
	intersecs3 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(1, 0, 0), new_vec(0, 1, 0));
	ray2 = eng_new_ray(new_point(0, 0, 0), new_vec(0, 1, 0));
	ray3 = eng_new_ray(new_point(0, 0, -5), new_vec(1, 1, 1));
	cylinder = eng_new_cylinder();
	direction = norm(ray.direct);
	eng_intersc_ray_cylinder(&intersecs, ray, &cylinder);
	eng_intersc_ray_cylinder(&intersecs2, ray2, &cylinder);
	eng_intersc_ray_cylinder(&intersecs3, ray3, &cylinder);
	eng_sort_intersc(&intersecs);
	eng_sort_intersc(&intersecs2);
	eng_sort_intersc(&intersecs3);
	if (intersecs.count == 0 && intersecs2.count == 0 && intersecs3.count == 0)
		result = true;
	else
		printf("RAY1 Intersecs Count: %d\nRAY2 Intersecs Count: %d\nRAY3 Intersecs Count: %d\n", \
			intersecs.count, intersecs2.count, intersecs3.count);
	return (result);
}
