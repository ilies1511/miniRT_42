#include <ft_engine.h>
#include <ft_tuple.h>
#include <libft.h>

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

