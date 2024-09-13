#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>


bool	test_mtx_sub_matrix(void)
{
	bool			ret = true;
	t_matrix		actual;
	t_matrix	test;
	t_matrix	expect;
	test.type = MAT3X3;
	test.m[0][0] = 1;
	test.m[0][1] = 5;
	test.m[0][2] = 0;
	test.m[1][0] = -3;
	test.m[1][1] = 2;
	test.m[1][2] = 7;
	test.m[2][0] = 0;
	test.m[2][1] = 6;
	test.m[2][2] = -3;
	expect.type = MAT2X2;
	expect.m[0][0] = -3;
	expect.m[0][1] = 2;
	expect.m[1][0] = 0;
	expect.m[1][1] = 6;

	actual = mtx_sub_matrix(test, 0, 2);
	if (!mtx_eq(actual, expect))
	{
		ft_fprintf(2, "Error: mtx_sub_matrix\nExpected: ");
		mtx_print(2, expect);
		ft_fprintf(2, "Actual: ");
		mtx_print(2, actual);
		ft_fprintf(2, "intput: ");
		mtx_print(2, test);
		ret = false;
	}
	const t_matrix test_2 = {
		.m = {
			{-6, 1, 1, 6},
			{-8, 5, 8, 6},
			{-1, 0, 8, 2},
			{-7, 1, -1, 1}
		},
		.type = MAT4X4,
	};
	t_matrix expect_2 = {
		.m = {
			{-6, 1, 6},
			{-8, 8, 6},
			{-7, -1, 1}
		},
		.type = MAT3X3
	};
	actual = mtx_sub_matrix(test_2, 2, 1);
	if (!mtx_eq(actual, expect_2))
	{
		ft_fprintf(2, "Error: mtx_sub_matrix_4x4\nExpected: ");
		mtx_print(2, expect_2);
		ft_fprintf(2, "Actual: ");
		mtx_print(2, actual);
		ft_fprintf(2, "intput: ");
		mtx_print(2, test_2);
		ret = false;
	}
	return (ret);
}

bool	test_mtx_cofactor(void)
{
	bool		ret = true;
	t_matrix	m = {.m = {
		{3, 5, 0},
		{2, -1, -7},
		{6, -1, 5},
	},
	.type = MAT3X3
	};
	float actual = mtx_cofactor(m, 0, 0);
	float expected = -12;
	if (!eq_f(actual, expected))
	{
		ft_fprintf(2, "test failed: mtx_cofactor\ninput:");
		mtx_print(2, m);
		ft_fprintf(2, "expected_output: %f\nactual output: %f\n", expected, actual);
		ret = false;
	}
	return (ret);
}

bool	test_mtx_det(void)
{
	bool	ret = true;
	float	actual;
	float	expected;

	t_matrix	test1 = {.m = {
			{1, 2, 6},
			{-5, 8, -4},
			{2, 6, 4},
		},
		.type = MAT3X3
	};
	if (!eq_f(mtx_cofactor(test1, 0, 0), 56)
			|| !eq_f(mtx_cofactor(test1, 0, 1), 12)
			|| !eq_f(mtx_cofactor(test1, 0, 2), -46))
	{
		ret = false;
		ft_fprintf(2, "test failed: mtx_cofactor: %s line %d\n", __FILE__, __LINE__);
	}
	expected = -196;
	actual = mtx_det(test1);
	if (!eq_f(actual, expected))
	{
		ret = false;
		ft_fprintf(2, "test failed: mtx_det: %s line %d\n", __FILE__, __LINE__);
		ft_fprintf(2, "input: ");
		mtx_print(2, test1);
		ft_fprintf(2, "expected: %f; actual: %f\n", expected, actual);
	}
	t_matrix	test2 = {.m = {
			{-2, -8, 3, 5},
			{-3, 1, 7, 3},
			{1, 2, -9, 6},
			{-6, 7, 7, -9},
		},
		.type = MAT4X4
	};
	if (!eq_f(mtx_cofactor(test2, 0, 0), 690)
			|| !eq_f(mtx_cofactor(test2, 0, 1), 447)
			|| !eq_f(mtx_cofactor(test2, 0, 2), 210)
			|| !eq_f(mtx_cofactor(test2, 0, 3), 51))
	{
		ret = false;
		ft_fprintf(2, "test failed: mtx_cofactor 4x4: %s line %d\n", __FILE__, __LINE__);
	}
	expected = -4071;
	actual = mtx_det(test2);
	if (!eq_f(actual, expected))
	{
		ret = false;
		ft_fprintf(2, "test failed: mtx_det 4x4: %s line %d\n", __FILE__, __LINE__);
		ft_fprintf(2, "input: ");
		mtx_print(2, test2);
		ft_fprintf(2, "expected: %f; actual: %f\n", expected, actual);
	}
	return (ret);
}
