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

double	kahan_sum_d(double *nbs, size_t count)
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
float	kahan_sum(float *nbs, size_t count)
{
	size_t	i;
	float	sum;
	float	next_add;
	float	compensation;
	float	total;

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
