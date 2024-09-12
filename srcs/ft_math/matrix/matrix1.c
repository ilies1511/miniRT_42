#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>
#include <main.h>

t_matrix	new_ident_m(t_matrix_type type)
{
	t_matrix	m;
	int			i;

	ft_bzero(&m, sizeof m);
	m.type = type;
	i = 0;
	while (i < (int)type)
	{
		m.m[i][i] = 1.0;
		i++;
	}
	return (m);
}

bool	eq_m(t_matrix ma, t_matrix mb)
{
	uint8_t	row;
	uint8_t	col;


	if (ma.type != mb.type)
		return (false);
	row = 0;
	while (row < ma.type)
	{
		col = 0;
		while (col < ma.type)
		{
			if (!eq_f(ma.m[row][col], mb.m[row][col]))
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}

t_tuple	mult_mt(t_matrix m, t_tuple tup)
{
	t_tuple	res;

	ft_bzero(&res, sizeof res);
	ft_assert(m.type == MAT4X4, __FILE__, __LINE__,
		"mult_mt: given matrix is not 4x4");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.arr[i] += m.m[i][j] * tup.arr[j];
		}
	}
	return (res);
}

// assumes a 4x4 matrix
t_matrix	mult_mm(t_matrix ma, t_matrix mb)
{
	t_matrix	ret;
	int			i;
	int			j;
	int			k;

	ft_assert(ma.type == MAT4X4 && mb.type == MAT4X4, __FILE__, __LINE__,
			"Error: matrix multiplication of wrong matrix type");
	ft_bzero(&ret, sizeof ret);
	ret.type = MAT4X4;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				ret.m[i][k] += ma.m[i][j] * mb.m[j][k];
				k++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

//tests
t_matrix	get_rdm_m(t_matrix_type type)
{

	t_matrix	m;

	if (type)
		m.type = type;
	else
		m.type = (t_matrix_type)(rand() % 3) + 2;
	for (int row = 0; row < (int)(m.type); row++)
	{
		for (int col = 0; col < (int)(m.type); col++)
		{
			m.m[row][col] = ((float)rand()) / rand();
		}
	}
	return (m);
}

void	print_m(t_fd fd, t_matrix m)
{
	int	row;
	int	col;

	ft_fprintf(fd, "%dx%dMatrix:\n", (int)m.type, (int)m.type);
	row = 0;
	while (row < (int)m.type)
	{
		col = 0;
		ft_fprintf(fd, "|");
		while (col < (int)m.type)
		{
			ft_fprintf(fd, "%f|", m.m[row][col]);
			col++;
		}
		ft_fprintf(fd, "\n");
		row++;
	}
}

bool	test_eq_m(void)
{
	t_matrix	last;
	t_matrix	cur;
	bool		ret;

	last = get_rdm_m(0);
	ret = true;
	for (int i = 0; i < 10000; i++)
	{
		cur = get_rdm_m(0);
		if (eq_m(last, cur))
		{
			ft_fprintf(2, "random matrixes seem to be the same, likely eq_m()\
				error. Tho it is possible that these two are the same:\n");
			print_m(2, last);
			print_m(2, cur);
			ft_fprintf(2, "if the above 2 are the same rerun the tests since\
				this was counted as a fail");
			ret = false;
		}
		last = cur;
		if (!eq_m(last, cur))
		{
			ft_fprintf(2, "eq_m() said identical matrixes are not the same:\n");
			print_m(2, last);
			print_m(2, cur);
			ret = false;
		}
	}
	return (ret);
}

bool	test_mult_mt(void)
{
	t_matrix	m;
	t_tuple		t;
	t_tuple		expect;
	t_tuple		actual;
	bool		ret;

	ret	= true;
	m = new_ident_m(MAT4X4);
	// test that multipling with the ident mat does return the input tuple
	for (int i = 0; i < 100; i++)
	{
		t = get_rdm_tuple();
		expect = t;
		actual = mult_mt(m, t);
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
	t_matrix actual_m = mult_mm(ma, mb);
	if (!eq_m(actual_m, expected_m))
	{
		ft_fprintf(2, "Error: mult_mm(): multipling the matrix:\n");
		print_m(2, ma);
		ft_fprintf(2, "with the matrix:\n");
		print_m(2, mb);
		ft_fprintf(2, "resulted in matrix:\n");
		print_m(2, actual_m);
		ft_fprintf(2, "expected matrix:\n");
		print_m(2, expected_m);
		ret = false;
	}
	// TODO: enter more tests here for specific inputs
	return (ret);
}

