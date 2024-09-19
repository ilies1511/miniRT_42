#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

t_tuple	mtx_mult_mt(t_matrix m, t_tuple tup)
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
t_matrix	mtx_mult_mm(t_matrix ma, t_matrix mb)
{
	t_matrix	ret;
	int			i;
	int			j;
	int			k;

	ft_assert(ma.type == MAT4X4 && mb.type == MAT4X4, __FILE__, __LINE__,
			"Error: matrix multiplication_mm of wrong matrix type");
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
				ft_assert(
					fabs((double)ma.m[i][j] * (double)mb.m[j][k] + (double)ret.m[i][k])
					< FLT_MAX,
					__FILE__, __LINE__, "Error: float overflow mtx_mult_mm");
				ret.m[i][k] += ma.m[i][j] * mb.m[j][k];
				k++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}
