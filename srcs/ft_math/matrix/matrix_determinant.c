#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

t_matrix	mtx_sub_matrix(t_matrix m, int remove_row, int remove_col)
{
	t_matrix	sub;
	int			old_row;
	int			old_col;
	int			new_row;
	int			new_col;

	ft_assert(m.type > MAT2X2 && remove_col < (int)m.type
			&& remove_row < (int)m.type,
		__FILE__, __LINE__, "mtx_sub_matrix invalid input");
	sub.type = m.type - 1;
	new_row = 0;
	old_row = 0;
	while (old_row < (int)m.type)
	{
		old_col = 0;
		new_col = 0;
		while (old_col < (int)m.type)
		{
			if (old_col != remove_col && old_row != remove_row)
				sub.m[new_row][new_col] = m.m[old_row][old_col];
			if (old_col != remove_col)
				new_col ++;
			old_col++;
		}
		if (old_row != remove_row)
			new_row++;
		old_row++;
	}
	return (sub);
}
/*
	“determinant of the submatrix"
*/
float	mtx_minor(t_matrix m, int row, int col)
{
	float		minor;
	t_matrix	sub_m;

	sub_m = mtx_sub_matrix(m, row, col);
	minor = mtx_det(sub_m);
	return (minor);
}

float	mtx_cofactor(t_matrix m, int row, int col)
{
	int		sign;

	sign = 1;
	if ((row + col) % 2)
		sign = -1;
	return (sign * mtx_minor(m, row, col));
}


//determinant
float	mtx_det(t_matrix m)
{
	float		result;

	result = 0;
	if (m.type > MAT2X2)
	{
		// result += mtx_det(mtx_sub_matrix(m, ...));
		return (result);
	}
	else
		return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
}
