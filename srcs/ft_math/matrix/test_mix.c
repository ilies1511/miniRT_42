#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>


//TODO: our calculation are quite inaccurate (precision issues)
//mtx_eq_roughly makes the test pass but the floating point error is more than
//0.01 sometimes when chainng calculation like this
bool	test_matrix_mult_inverse(void)
{
	bool	ret = true;

	t_matrix ma = {
		.m = {
			{3, -9, 7, 3},
			{3, -8, 2, -9},
			{-4, 4, 4, 1},
			{-6, 5, -1, 1},
		},
		.type = MAT4X4,
	};
	t_matrix mb = {
		.m = {
			{8, 2, 2, 2},
			{3, -1, 7, 0},
			{7, 0, 5, 4},
			{6, -2, 0, 5},
		},
		.type = MAT4X4,
	};
	t_matrix	prod = mtx_mult_mm(ma, mb);
	t_matrix	mib= mtx_inverse(mb);
	t_matrix	res = mtx_mult_mm(prod, mib);
	if (!mtx_eq(res, ma))
	{
		ret = false;
		ft_printf("test failed: mtx_mult_mm()->mtx_inverse()->mtx_mult_mm():\
				%s line %s\n", __FILE__, __LINE__);
	}
	for (int i = 0; i < 100000; i++)
	{
		ma = mtx_get_rdm_m(MAT4X4);
		mb = mtx_get_rdm_m(MAT4X4);
		if (fabs(mtx_det(mb)) < EPSILON * 10)
			continue ;
		prod = mtx_mult_mm(ma, mb);
		mib = mtx_inverse(mb);
		res = mtx_mult_mm(prod, mib);
		if (!mtx_eq_roughly(res, ma))
		{
			ret = false;
			ft_fprintf(2, "test failed: mtx_mult_mm()->mtx_inverse()->mtx_mult_mm():\
					%s line %d\n", __FILE__, __LINE__);
			ft_fprintf(2, "mb: ");
			mtx_print(2, mb);
			ft_fprintf(2, "prod: ");
			mtx_print(2, prod);
			ft_fprintf(2, "mib: ");
			mtx_print(2, mib);
			ft_fprintf(2, "ma(expected): ");
			mtx_print(2, ma);
			ft_fprintf(2, "res(actual): ");
			mtx_print(2, res);
		}
	}
	return (ret);
}
