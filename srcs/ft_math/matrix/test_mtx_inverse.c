#include <ft_matrix.h>
#include <libft.h>

bool	test_mtx_inverse(void)
{
	bool		ret = true;
	t_matrix	actual;

	t_matrix test1 = {
		.m = {
			{-5, 2, 6, -8},
			{1, -5, 1, 8},
			{7, 7, -6, -7},
			{1, -3, 7, 4},
		},
		.type = MAT4X4,
	};
	t_matrix expected = {
		.m = {
			{0.21805, 0.45113, 0.24060, -0.04511},
			{-0.80827, -1.45677, -0.44361, 0.52068},
			{-0.07895, -0.22368, -0.05263, 0.19737},
			{-0.52256, -0.81391, -0.30075, 0.30639},
		},
		.type = MAT4X4,
	};
	actual = mtx_inverse(test1);
	if (!mtx_eq(actual, expected))
	{
		ret = false;
		ft_fprintf(2, "Test failed: mtx_inverse: input:");
		mtx_print(2, test1);
		ft_fprintf(2, "expected: ");
		mtx_print(2, expected);
		ft_fprintf(2, "actual: ");
		mtx_print(2, actual);
	}
	return (ret);
}
