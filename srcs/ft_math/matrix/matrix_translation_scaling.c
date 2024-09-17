#include <ft_matrix.h>

t_matrix	mtx_translation_izi(t_tuple tuple)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] = tuple.x;
	ret.m[1][3] = tuple.y;
	ret.m[2][3] = tuple.z;
	return (ret);
}

/*
	ret.m[0][3] += x;
	Warum "+="
*/
t_matrix	mtx_translation(float x, float y, float z)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] += x;
	ret.m[1][3] += y;
	ret.m[2][3] += z;
	return (ret);
}

// TODO:
t_matrix	mtx_scale(float x, float y, float z)
{
	t_matrix	ret;

	(void)x;
	(void)y;
	(void)z;
	ret = mtx_new_ident(MAT4X4);
	return (ret);
}

// TODO:
// also needs some kind of struct for arguement to pass norm
t_matrix	mtx_skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix	ret;

	(void)xy;
	(void)xz;
	(void)yx;
	(void)yz;
	(void)zx;
	(void)zy;
	ret = mtx_new_ident(MAT4X4);
	return (ret);
}
