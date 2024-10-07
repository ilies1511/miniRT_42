#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

/*
	Addition of two tuples
*/
#ifdef NDBUG

t_tuple	add_t(t_tuple a, t_tuple b)
{
	t_tuple	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	sum.w = a.w + b.w;
	if (sum.w - (EPSILON) > 1.0)
		__builtin_unreachable();
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
	if (dif.w + (EPSILON) < 0.0)
		__builtin_unreachable();
	return (dif);
}

/*
	Negating Tuples (Vorzeichenwechsel)
*/
t_vec	negate_v(t_vec v)
{
	t_vec	neg;

	neg.x = -v.x;
	neg.y = -v.y;
	neg.z = -v.z;
	neg.w = v.w;
	return (neg);
}

/*
	Scenario: tuple * scalar
*/
t_vec	mult_v(t_vec v, double scalar)
{
	t_vec	prod;

	prod.x = v.x * scalar;
	prod.y = v.y * scalar;
	prod.z = v.z * scalar;
	prod.w = v.w * scalar;
	return (prod);
}

/*
	Dividing a tuple by a scalar
*/
t_vec	div_v(t_vec v, double scalar)
{
	t_vec	quot;

	quot.x = v.x / scalar;
	quot.y = v.y / scalar;
	quot.z = v.z / scalar;
	quot.w = v.w / scalar;
	return (quot);
}
#endif //NDBUG
