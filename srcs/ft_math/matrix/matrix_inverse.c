#include <ft_matrix.h>
#include <ft_floats.h>
#include <libft.h>

// inefficnet basic
t_matrix	mtx_inverse(t_matrix m)
{
	t_matrix	inv;
	int			row;
	int			col;
	float		det;

	ft_assert(!eq_f(mtx_det(m), 0.0), __FILE__, __LINE__, "Error: matrix\
			given to mtx_inverse() is not invertable (det == 0)");
	det = mtx_det(m);
	row = 0;
	while (row < (int)m.type)
	{
		col = 0;
		while (col < (int)m.type)
		{
			inv.m[col][row] = mtx_cofactor(m, row, col) / det;
			col++;
		}
		row++;
	}
	inv.type = m.type;
	return (inv);
}
//t_matrix	mtx_inverse(t_matrix m)
//{
//	t_matrix	inv;
//	t_matrix	cofac;
//	int			row;
//	int			col;
//	float		det;
//
//	cofac.type = m.type;
//	inv.type = m.type;
//	row = 0;
//	det = mtx_det(m);
//	while (row < (int)m.type)
//	{
//		col = 0;
//		while (col < (int)m.type)
//		{
//			cofac.m[row][col] = mtx_cofactor(m, row, col);
//			col++;
//		}
//		row++;
//	}
//	cofac = mtx_transpose(cofac);
//	row = 0;
//	while (row < (int)m.type)
//	{
//		col = 0;
//		while (col < (int)m.type)
//		{
//			inv.m[row][col] = cofac.m[row][col] / det;
//			col++;
//		}
//		row++;
//	}
//	return (inv);
//}
