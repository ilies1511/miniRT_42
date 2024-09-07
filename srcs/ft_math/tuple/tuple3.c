#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

float	len_v(t_vec v)
{
#ifndef NDBUG//can be removed later
	ft_assert(is_vec(v), __FILE__, __LINE__, "getting length of a none vector");
#endif
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_vec	norm(t_vec v)
{
	float	len;

	len = len_v(v);
#ifndef NDBUG
	ft_assert(!eq_f(len, 0.0), __FILE__, __LINE__, "normalizing a vec with len 0");
#endif
	return (div_v(v, len));
}

float	dot_prod(t_vec a, t_vec b)
{
#ifndef NDBUG//can be removed later
	ft_assert(is_vec(a) && is_vec(b), __FILE__, __LINE__,
		"getting dot product of a none vector");
#endif
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w
	);
}

t_vec	cross_prod(t_vec a, t_vec b)
{
#ifndef NDBUG//can be removed later
	ft_assert(is_vec(a) && is_vec(b), __FILE__, __LINE__,
		"getting corss product of a none vector");
#endif
	return (new_vec(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x));
}

