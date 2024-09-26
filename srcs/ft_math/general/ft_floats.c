#include <ft_floats.h>

bool	eq_f(double a, double b)
{
	if (fabsl(a - b) <= EPSILON)
		return (true);
	return (false);
}

bool	less_eq_f(double a, double b)
{
	if (a < b || eq_f(a, b))
		return (true);
	return (false);
}

bool	greater_eq_f(double a, double b)
{
	if (a > b || eq_f(a, b))
		return (true);
	return (false);
}

double	clamp_f(double nb, double min, double max)
{
	return (fmaxl(min, fminl(nb, max)));
}
