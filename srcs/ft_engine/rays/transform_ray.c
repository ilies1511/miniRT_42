#include <main.h>
#include <ft_matrix.h>
#include <ft_engine.h>

t_ray	eng_transform_ray(t_ray ray, t_matrix transform)
{
	t_ray	ret;

	ret.origin = mtx_mult_mt(transform, ray.origin);
	ret.direct = mtx_mult_mt(transform, ray.direct);
	return (ret);
}

