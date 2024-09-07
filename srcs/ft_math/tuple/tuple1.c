#include <ft_tuple.h>
#include <ft_floats.h>

bool	is_vec(t_tuple tuple)
{
	if (eq_f(tuple.w, 0.0))
		return (true);
	return (false);
}

bool	is_point(t_tuple t)
{
	if (eq_f(t.w, 1.0))
		return (true);
	return (false);
}

t_point	new_point(float x, float y, float z);
t_vec	new_vec(float x, float y, float z);
bool	eq_t(t_tuple a, t_tuple b);


