#include <ft_floats.h>

bool	eq_f(float a, float b)
{
	if (fabs(a - b) <= EPSILON)
		return (true);
	return (false);
}

