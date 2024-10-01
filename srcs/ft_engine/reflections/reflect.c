#include <ft_engine.h>
#include <main.h>

t_vec	ref_reflect(t_vec vec, t_vec surface_normal)
{
	double	dot;
	t_vec	scaled_normal;

	dot = dot_prod(vec, surface_normal);
	scaled_normal = mult_v(surface_normal, 2 * dot);
	return (sub_t(vec, scaled_normal));
}

t_fcolor	ref_reflected_color(t_world world, t_computation comp)
{

}

bool	test_ref_reflect_color(void)
{
	bool	ret = true;
	t_world	world = eng_default_world();

	return (ret);
}
