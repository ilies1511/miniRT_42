#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

bool	test_mtx_mult_mt(void)
{
	t_matrix	m;
	t_tuple		t;
	t_tuple		expect;
	t_tuple		actual;
	bool		ret;

	ret	= true;
	m = mtx_new_ident(MAT4X4);
	// test that multipling with the ident mat does return the input tuple
	for (int i = 0; i < 100; i++)
	{
		t = get_rdm_tuple();
		expect = t;
		actual = mtx_mult_mt(m, t);
		if (!eq_t(expect, actual))
		{
			ft_fprintf(2, "Error: mult_mt(): multipling the tuple:\n");
			print_t(2, t);
			ft_fprintf(2, "with the ident matrix resulted in:\n");
			print_t(2, actual);
			ret = false;
		}
	}
	m = get_rdm_m(MAT4X4);
	// TODO: enter more tests here for specific inputs
	return (ret);
}

bool	test_mtx_mult_mm(void)
{
	bool	ret;

	ret = true;
	t_matrix ma = {
		.m = {
    {0.04494985f, 1.01111161f, 0.77070470f, 1.33838639f},
    {1.77777978f, 0.77979580f, 0.99494094f, 1.99191191f},
    {1.99494194f, 1.33535636f, 1.22222523f, 0.22626927f},
    {0.66767067f, 0.88585485f, 0.33131231f, 0.22424625f}
		},
		.type = MAT4X4,
	};
	t_matrix mb = {
		.m = {
    {0.33636436f, 1.55353954f, 1.88686486f, 0.06676737f},
    {2.88383383f, 0.22121321f, 0.05525235f, 0.06636306f},
    {15.44040140f, 6.44040140f, 0.77171171f, 3.99696597f},
    {1.33434234f, 0.11616216f, 1.33434234f, 0.44040140f}
		},
		.type = MAT4X4,
	};
	t_matrix	expected_m = {
		.m = {
			{16.61685295f, 5.41262010f, 2.52130805f, 3.74000934f},
			{20.86696315f, 9.57355613f, 6.82321572f, 5.02443319f},
    		{23.69554203f, 11.29252466f, 5.08309361f, 5.20665732f},
    		{8.19405512f,  3.39304877f,  1.86364874f, 1.52636904f},
		},
		.type = MAT4X4,
	};
	t_matrix actual_m = mtx_mult_mm(ma, mb);
	if (!mtx_eq(actual_m, expected_m))
	{
		ft_fprintf(2, "Error: mult_mm(): multipling the matrix:\n");
		mtx_print(2, ma);
		ft_fprintf(2, "with the matrix:\n");
		mtx_print(2, mb);
		ft_fprintf(2, "resulted in matrix:\n");
		mtx_print(2, actual_m);
		ft_fprintf(2, "expected matrix:\n");
		mtx_print(2, expected_m);
		ret = false;
	}
	return (ret);
}

