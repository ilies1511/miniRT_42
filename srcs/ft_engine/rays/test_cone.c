#include <main.h>
#include <ft_engine.h>
#include <libft.h>

bool	test_cone_intersect(void)
{
	bool			result;
	t_intersc_arr	intersecs;
	t_intersc_arr	intersecs2;
	t_intersc_arr	intersecs3;
	t_cone			cone;
	t_ray			ray;

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
	printf("TEST 11:\nMY t1: %lf vs. OG: %d\nMY t2: %lf vs. OG: %d\n", \
			intersecs.arr[0].t, 5, intersecs.arr[1].t, 5);
	//TEST2
	intersecs2 = eng_new_intersc_arr();
	ray = eng_new_ray(new_point(0, 0, -5), new_vec(1, 1, 1));
	ray.direct = norm(ray.direct);
	eng_intersc_ray_cone(&intersecs2, ray, &cone);
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
	printf("%s Line %d\n", __FILE__, __LINE__);
	printf("TEST 2:\nMY t1 : %lf vs. OG: %lf\nMY t2: %lf vs. OG: %lf\n", \
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
	eng_free_intersc_arr(&intersecs3);
	return (result);
}
