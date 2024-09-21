#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

/*
	Addition of two tuples
*/
t_tuple	add_t(t_tuple a, t_tuple b)
{
	t_tuple	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	sum.w = a.w + b.w;
#ifndef NDBUG//can be removed later
			 //keep for now to find bugs
			 //is ignore with 'make fast' to imrprove perfomance
		ft_assert(less_eq_f(sum.w , 1.0), __FILE__, __LINE__,
			"sum of 2 tuples is > 1.0, added 2 points?");
#else
	if (sum.w + EPSILON > 1.0)
		__builtin_unreachable();
#endif //NDBUG
	return (sum);
}

/*
	Subtraction of two tuples
*/
t_tuple	sub_t(t_tuple a, t_tuple b)
{
	t_tuple	dif;

	dif.x = a.x - b.x;
	dif.y = a.y - b.y;
	dif.z = a.z - b.z;
	dif.w = a.w - b.w;
#ifndef NDBUG//can be removed later
			 //keep for now to find bugs
			 //is ignore with 'make fast' to imrprove perfomance
		ft_assert(greater_eq_f(dif.w , 0.0), __FILE__, __LINE__,
			"dif of 2 tuples is < 0.0, subtracted a point from a vector?");
#else
	if (dif.w + EPSILON < 0.0)
		__builtin_unreachable();
#endif //NDBUG
	return (dif);
}

/*
	Negating Tuples (Vorzeichenwechsel)
*/
t_vec	negate_v(t_vec v)
{
#ifndef NDBUG//can be removed later
	ft_assert(is_vec(v), __FILE__, __LINE__, "negating a none vector");
#endif
	t_vec	neg;

	neg.x = -v.x;
	neg.y = -v.y;
	neg.z = -v.z;
	neg.w = v.w;
#ifndef NDBUG//can be removed later
	t_tuple	dif = add_t(v, neg);
	ft_assert(eq_f(dif.x, 0.0) && eq_f(dif.y, 0.0) && eq_f(dif.z, 0.0),
		__FILE__, __LINE__,
		"negation + base != 0, maybe a zero devison somewhere leading to INF?");
#endif //NDBUG
	return (neg);
}

/*
	Scenario: tuple * scalar
*/
t_vec	mult_v(t_vec v, float scalar)
{
#ifndef NDBUG//can be removed later
	ft_assert(is_vec(v), __FILE__, __LINE__, "multiplying a none vector");
#endif
	t_vec	prod;

	prod.x = v.x * scalar;
	prod.y = v.y * scalar;
	prod.z = v.z * scalar;
	prod.w = v.w * scalar;
#ifndef NDBUG
	ft_assert(scalar != INFINITY, __FILE__, __LINE__, "multiplied by infinity");
#endif
	return (prod);
}

/*
	Dividing a tuple by a scalar
*/
t_vec	div_v(t_vec v, float scalar)
{
#ifndef NDBUG
	ft_assert(!eq_f(scalar, 0.0), __FILE__, __LINE__, "zero devision");
	ft_assert(is_vec(v), __FILE__, __LINE__, "deviding a none vector");
#endif
	t_vec	quot;

	quot.x = v.x / scalar;
	quot.y = v.y / scalar;
	quot.z = v.z / scalar;
	quot.w = v.w / scalar;
	return (quot);
}
