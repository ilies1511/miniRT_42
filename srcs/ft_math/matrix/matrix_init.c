#include <ft_matrix.h>
#include <libft.h>

t_matrix	mtx_new_ident(t_matrix_type type)
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

//for tests and bebugging
t_matrix	mtx_get_rdm_m(t_matrix_type type)
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
