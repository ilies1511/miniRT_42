#include <ft_engine.h>
#include <main.h>

t_vec	eng_reflect(t_vec vec, t_vec surface_normal)
{
	float	dot;
	t_vec	scaled_normal;

	dot = dot_prod(vec, surface_normal);
	scaled_normal = mult_v(surface_normal, 2 * dot);
	return (sub_t(vec, scaled_normal));
}

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
	actual = eng_reflect(vec, normal);
	if (!eq_t(expect, actual))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_refelct: %s line %d\n", __FILE__, __LINE__);
		print_t(2, actual);
	}
	vec = new_vec(0, -1, 0);
	normal = new_vec(sqrt(2)/2, sqrt(2)/2, 0);
	expect = new_vec(1, 0, 0);
	actual = eng_reflect(vec, normal);
	if (!eq_t(expect, actual))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_reflect: %s line %d\n", __FILE__, __LINE__);
		print_t(2, actual);
	}
	return (ret);
}
