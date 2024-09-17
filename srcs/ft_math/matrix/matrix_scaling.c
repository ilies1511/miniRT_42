#include <ft_matrix.h>

// // TODO:
t_matrix	mtx_scale(float x, float y, float z)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][0] = x;
	ret.m[1][1] = y;
	ret.m[2][2] = z;
	return (ret);
}

// TODO: 17.09.2024
t_matrix	mtx_scale_izi(t_tuple tuple)
{
	t_matrix	ret;
	int			i;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][0] = tuple.x;
	ret.m[1][1] = tuple.y;
	ret.m[2][2] = tuple.z;
	return (ret);
}
