#include <ft_matrix.h>
#include <libft.h>

t_matrix	mtx_new_ident(t_matrix_type type)
{
	t_matrix	m;
	int			i;
	int			j;

	ft_bzero(&m, sizeof m);
	m.type = type;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[j][i] = 1.0;
			else
				m.m[j][i] = 0.0;
			j++;
		}
		i++;
	}
	return (m);
}

//for tests and bebugging
t_matrix	mtx_get_rdm_m(t_matrix_type type)
{
	t_matrix	m;
	int			row;
	int			col;

	if (type)
		m.type = type;
	else
		m.type = (t_matrix_type)(rand() % 3) + 2;
	row = 0;
	while (row < (int)(m.type))
	{
		col = 0;
		while (col < (int)(m.type))
		{
			m.m[row][col] = ((double)rand()) / rand();
			col++;
		}
		row++;
	}
	return (m);
}
