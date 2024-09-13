#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

void	mtx_print(t_fd fd, t_matrix m)
{
	int	row;
	int	col;

	fprintf(stderr, "%dx%dMatrix:\n", (int)m.type, (int)m.type);
	row = 0;
	ft_assert(m.type >= MAT2X2 && m.type <= MAT4X4, __FILE__, __LINE__,
			"Error: mtx_print: invalid matrix type");
	while (row < (int)m.type)
	{
		col = 0;
		// ft_fprintf(fd, "[ ");
		fprintf(stderr, "[ ");
		while (col < (int)m.type)
		{
			// ft_fprintf(fd, "%f\t", m.m[row][col]);
			fprintf(stderr, "%10f", m.m[row][col]);
			col++;
			if (col < (int)m.type)
				fprintf(stderr, "\t");
		}
		// ft_fprintf(fd, "]\n");
		fprintf(stderr, "]\n");
		row++;
	}
	(void)fd;
}

bool	mtx_eq(t_matrix ma, t_matrix mb)
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

bool	mtx_eq_roughly(t_matrix ma, t_matrix mb)
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
			if (fabs(ma.m[row][col] - mb.m[row][col]) > EPSILON * 1000)
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}
