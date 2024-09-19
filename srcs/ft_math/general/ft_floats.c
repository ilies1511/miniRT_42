#include <ft_floats.h>

bool	eq_f(float a, float b)
{
	if (fabs(a - b) <= EPSILON)
		return (true);
	return (false);
}

bool	less_eq_f(float a, float b)
{
	if (a < b || eq_f(a, b))
		return (true);
	return (false);
}

bool	greater_eq_f(float a, float b)
{
	if (a > b || eq_f(a, b))
		return (true);
	return (false);
}

float	clamp_f(float nb, float min, float max)
{
	return (fmax(min, fmin(nb, max)));
}
