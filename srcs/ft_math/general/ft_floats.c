#include <ft_floats.h>

bool	eq_f(double a, double b)
{
	if (fabsl(a - b) <= (EPSILON))
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

double	kahan_sum(double *nbs, size_t count)
{
	size_t	i;
	double	sum;
	double	next_add;
	double	compensation;
	double	total;

	i = 0;
	sum = 0.0;
	compensation = 0.0;
	total = 0.0;
	while (i < count)
	{
		next_add = nbs[i] - compensation;
		total = sum + next_add;
		compensation = (total - sum) - next_add;
		sum = total;
		i++;
	}
	return (sum);
}
