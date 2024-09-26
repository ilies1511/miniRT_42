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

t_point	new_point(double x, double y, double z)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = 1.0;
	return (new);
}

t_vec	new_vec(double x, double y, double z)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = 0.0;
	return (new);
}

bool	eq_t(t_tuple a, t_tuple b)
{
	return (eq_f(a.x, b.x)
		&& eq_f(a.y, b.y)
		&& eq_f(a.z, b.z)
		&& eq_f(a.w, b.w)
	);
}

