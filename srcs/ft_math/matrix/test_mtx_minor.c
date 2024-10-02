#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

static int	mtx_compare_floats(double a, double b)
{
	return (fabs(a - b) < (EPSILON));
}

int	test_mtx_minor(void)
{
	// t_matrix	ist;
	double		ist;
	double		soll;

	t_matrix	pre =
	{
		.m = {
			{3, 5, 0},
			{2, -1, -7},
			{6, -1, 5}},
		.type = MAT3X3,
	};
	soll = 25;
	ist = mtx_minor(pre, 1, 0);
	if (!mtx_compare_floats(soll, ist))
	{
		printf("ERROR(minor): \nSOLL: %f vs. IST: %f\n", soll, ist);
		return (0);
	}
	return (1);
}
