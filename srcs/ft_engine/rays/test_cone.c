#include <main.h>
#include <ft_engine.h>
#include <libft.h>

bool	test_normal_cone(void)
{
	t_cone	cone;
	t_vec	ist;
	bool	result;

	result = true;
	cone = eng_new_cone();
	// ist = eng_normal_at(&cone, new_point(0, 0, 0));
	// if (!eq_t(ist, new_vec(0, 0, 0)))
	// {
	// 	printf("TEST1 normal_at_cone --> %s LINE: %d\n", __FILE__, __LINE__);
	// 	printf("IST: ");
	// 	print_t(2, ist);
	// 	printf("SOLL: ");
	// 	print_t(2, new_vec(0, 0, 0));
	// 	result = false;
	// }
	ist = eng_normal_at(&cone, new_point(1, 1, 1));
	if (!eq_t(ist,  norm(new_vec(1, -sqrtl(2), 1))))
	{
		printf("TEST2 normal_at_cone --> %s LINE: %d\n", __FILE__, __LINE__);
		printf("IST: ");
		print_t(2, ist);
		printf("SOLL: ");
		print_t(2, new_vec(1, -sqrtl(2), 1));
		result = false;
	}
	ist = eng_normal_at(&cone, new_point(-1, -1, 0));
	if (!eq_t(ist, norm(new_vec(-1, 1, 0))))
	{
		printf("TEST3 normal_at_cone --> %s LINE: %d\n", __FILE__, __LINE__);
		printf("IST: ");
		print_t(2, ist);
		printf("SOLL: ");
		print_t(2, new_vec(-1, 1, 0));
		result = false;
	}
	return (result);
}

bool	test_intersec_cone_caps(void)
{
	bool			result;
	t_cone			cone;
	t_ray			ray;
	t_intersc_arr	intersecs;

	result = true;
	cone = eng_new_cone();
	cone.max = 0.5;
	cone.min = -0.5;
	cone.closed = true;

	//TEST1
	intersecs = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 1, 0));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs, ray, &cone);
	if ((intersecs.count != 0))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("%s Line %d\nTEST1 --> Cone inrersecs count: %d vs. OG: %d\n", __FILE__, \
			__LINE__, intersecs.count, 0);
		result = false;
	}
	// TEST2
	eng_free_intersc_arr(&intersecs);
	intersecs = eng_new_intersc_arr();
	// printf("Pre Calculation Intersect Count: %d\n", intersecs.count);
	ray = eng_new_ray(new_point(0, 0, -0.25), new_vec(0, 1, 1));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs, ray, &cone);
	// printf("In test_intersecs_cone_caps: POST Calculation Intersect Count: %d\n", intersecs.count);
	if ((intersecs.count != 2))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("%s Line %d\nTEST2 --> Cone inrersecs count: %d vs. OG: %d\n", __FILE__, \
			__LINE__, intersecs.count, 2);
		printf("Intersecs Cone Caps :\nMY t1: %lf\nMY t2: %lf\nMY t3: %lf\nMY t4: %lf\nMY t5: %lf\n", \
			intersecs.arr[0].t, intersecs.arr[1].t, intersecs.arr[2].t, intersecs.arr[3].t, intersecs.arr[4].t);
		result = false;
	}
	// //TEST3
	eng_free_intersc_arr(&intersecs);
	intersecs = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 0, -0.25), new_vec(0, 1, 0));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs, ray, &cone);
	if ((intersecs.count != 4))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("%s Line %d\nTEST3 --> Cone inrersecs count: %d vs. OG: %d\n", __FILE__, \
			__LINE__, intersecs.count, 4);
		result = false;
	}
	return (result);
}

bool	test_parallel(void)
{
	bool			result;
	t_ray			ray;
	t_intersc_arr	intersecs;
	t_cone			cone;

	result = true;
	cone = eng_new_cone();
	intersecs = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 0, -1), new_vec(0, 1, 1));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs, ray, &cone);
	if ((!eq_f(intersecs.arr[0].t, 0.35355)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("Cone Parallel --> TEST 1:\nMY t1: %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs.arr[0].t, 0.35355, intersecs.arr[1].t, 0.35355);
		result = false;
		printf("%s Line %d\nTEST 0 --> Cone inrersecs count: %d\n", __FILE__, \
			__LINE__, intersecs.count);
	}
	// printf("%s Line %d\n", __FILE__, __LINE__);
	// printf("Cone Parallel --> TEST 1:\nMY t1: %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
		// intersecs.arr[0].t, 0.35355, intersecs.arr[1].t, 0.35355);
	// printf("%s Line %d\n Cone inrersecs count: %d\n", __FILE__, \
			// __LINE__, intersecs.count);
	return (result);
}

bool	test_cone_intersect(void)
{
	bool			result;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;
	t_cone			cone;
	t_ray			ray;
	t_ray			ray2;
	t_ray			ray3;

	result = true;
	cone = eng_new_cone();
	intersecs = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs, ray, &cone);
	//TEST0
	if (intersecs.count != 2)
		return (printf("%s Line %d\nTEST 0 --> Cone inrersecs count: %d\n", __FILE__, \
			__LINE__, intersecs.count), \
				eng_free_intersc_arr(&intersecs), false);
	//TEST1
	if ((intersecs.arr[0].t != 5) || (intersecs.arr[1].t != 5))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 1:\nMY t1: %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs.arr[0].t, 5, intersecs.arr[1].t, 5);
		result = false;
		return (result);
	}
	// printf("TEST 11:\nMY t1: %lf vs. OG: %d\nMY t2: %lf vs. OG: %d\n", \
			intersecs.arr[0].t, 5, intersecs.arr[1].t, 5);
	//TEST2
	intersecs2 = eng_new_intersc_arr();
	ray2 = eng_new_ray(new_point(0, 0, -5), new_vec(1, 1, 1));
	ray2.direct = norm(ray2.direct);
	eng_intersc_ray_cone(&intersecs2, ray2, &cone);
	if (intersecs2.count == 2)
	{
		if ((!eq_f(intersecs2.arr[0].t, 8.66025))
			|| (!eq_f(intersecs2.arr[1].t, 8.66025)))
		{
			printf("%s Line %d\n", __FILE__, __LINE__);
			printf("TEST 2:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
				intersecs2.arr[0].t, 8.66025, intersecs2.arr[1].t, 8.66025);
			result = false;
		}
	}
	else
		return (printf("%s Line %d\nTEST2 --> Cone inrersecs count Im here: %d\n", __FILE__, \
			__LINE__, intersecs2.count), \
				eng_free_intersc_arr(&intersecs2), false);
	// printf("%s Line %d\n", __FILE__, __LINE__);
	// printf("TEST 2:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs2.arr[0].t, 8.66025, intersecs2.arr[1].t, 8.66025);
	//TEST3
	intersecs3 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(1, 1, -5), new_vec(-0.5, -1, 1));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs3, ray, &cone);
	if ((!eq_f(intersecs3.arr[0].t, 4.55006))
		|| (!eq_f(intersecs3.arr[1].t, 49.44994)))
	{
		printf("%s Line %d\n", __FILE__, __LINE__);
		printf("TEST 3:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
			intersecs3.arr[0].t, 4.55006, intersecs3.arr[1].t, 49.44994);
		result = false;
	}
	// printf("%s Line %d\n", __FILE__, __LINE__);
	// printf("TEST 3:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
		intersecs3.arr[0].t, 4.55006, intersecs3.arr[1].t, 49.44994);
	eng_free_intersc_arr(&intersecs3);
	return (result);
}
