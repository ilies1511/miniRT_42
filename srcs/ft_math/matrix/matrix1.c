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
	int			i = 0;

	ft_assert(ma.type == MAT4X4 && mb.type == MAT4X4, __FILE__, __LINE__,
			"Error: matrix multiplication of wrong matrix type");
	ret.type = MAT4X4;
	while (i < 4)
	{
		ret.base_vecs[i] = mult_mt(ma, mb.base_vecs[i]);
		i++;
	}
	return (ret);
}

//tests
t_matrix	get_random_matrix(void)
{

	t_matrix	m;

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
	
	last = get_random_matrix();
	ret = true;
	for (int i = 0; i < 10000; i++)
	{
		cur = get_random_matrix();
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
	// TODO: enter tests here for specific inputs
	return (ret);
}

