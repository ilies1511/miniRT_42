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
	t_matrix expected1 = {
		.m = {
			{0.21805, 0.45113, 0.24060, -0.04511},
			{-0.80827, -1.45677, -0.44361, 0.52068},
			{-0.07895, -0.22368, -0.05263, 0.19737},
			{-0.52256, -0.81391, -0.30075, 0.30639},
		},
		.type = MAT4X4,
	};
	actual = mtx_inverse(test1);
	if (!mtx_eq(actual, expected1))
	{
		ret = false;
		ft_fprintf(2, "Test failed: mtx_inverse: input:");
		mtx_print(2, test1);
		ft_fprintf(2, "expected: ");
		mtx_print(2, expected1);
		ft_fprintf(2, "actual: ");
		mtx_print(2, actual);
	}
	t_matrix	test2 = {
		.m = {
			{8, -5, 9, 2},
			{7, 5, 6, 1},
			{-6, 0, 9, 6},
			{-3, 0, -9, -4},
		},
		.type = MAT4X4,
	};
	t_matrix	expected2 = {
		.m = {
			{-0.15385, -0.15385, -0.28205, -0.53846},
			{-0.07692, 0.12308, 0.02564, 0.03077},
			{0.35897, 0.35897, 0.43590, 0.92308},
			{-0.69231, -0.69231, -0.76923, -1.92308},
		},
		.type = MAT4X4,
	};
	actual = mtx_inverse(test2);
	if (!mtx_eq(actual, expected2))
	{
		ret = false;
		ft_fprintf(2, "Test failed: mtx_inverse: input:");
		mtx_print(2, test2);
		ft_fprintf(2, "expected: ");
		mtx_print(2, expected2);
		ft_fprintf(2, "actual: ");
		mtx_print(2, actual);
	}
	t_matrix	test3 = {
		.m = {
			{9, 3, 0, 9},
			{-5, -2, -6, -3},
			{-4, 9, 6, 4},
			{-7, 6, 6, 2},
		},
		.type = MAT4X4,
	};
	t_matrix	expected3 = {
		.m = {
			{-0.04074, -0.07778, 0.14444, -0.22222},
			{-0.07778, 0.03333, 0.36667, -0.33333},
			{-0.02901, -0.14630, -0.10926, 0.12963},
			{0.17778, 0.06667, -0.26667, 0.33333},
		},
		.type = MAT4X4,
	};
	actual = mtx_inverse(test3);
	if (!mtx_eq(actual, expected3))
	{
		ret = false;
		ft_fprintf(2, "Test failed: mtx_inverse: input:");
		mtx_print(2, test3);
		ft_fprintf(2, "expected: ");
		mtx_print(2, expected3);
		ft_fprintf(2, "actual: ");
		mtx_print(2, actual);
	}
	return (ret);
}
