#include <ft_matrix.h>

// TODO: izi
// also needs some kind of struct for arguement to pass norm
t_matrix	mtx_skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][1] = xy;
	ret.m[0][2] = xz;
	ret.m[1][0] = yx;
	ret.m[1][2] = yz;
	ret.m[2][0] = zx;
	ret.m[2][1] = zy;
	return (ret);
}
