#include <ft_matrix.h>
#include <math.h>

//NOTE: I dont know if these are part of the book since I havn't read that
//fully
	//I just wanted to implement these my self after finally understanding
//what the matrix multiplication does

// rotation on x-axis
// theta == 2 * M_PI ->full rotation
// default pitch: theta == 0
// theta == M_M_PI -> upside down
// 2_M_PI (M_PI / 2) -> the y axis is the orginal z axis,
//	the z axis is the inverse of the old y axis)
t_matrix	pitch_matrix(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[1][1] = cos(theta);
	mat.m[2][1] = sin(theta);
	mat.m[1][2] = -sin(theta);
	mat.m[2][2] = cos(theta);
	return (mat);
}

// rotation on z-axis
// theta == 0 ->default
// clock wise roll
t_matrix	roll_matrix(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[0][0] = cos(theta);
	mat.m[1][0] = sin(theta);
	mat.m[0][1] = -sin(theta);
	mat.m[1][1] = cos(theta);
	return (mat);
}

// rotation on y-axis
// theta == 0 ->default
// front rotation right to left
// back rotation left to right
t_matrix	yaw_matrix(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[0][0] = cos(theta);
	mat.m[2][0] = -sin(theta);
	mat.m[0][2] = sin(theta);
	mat.m[2][2] = cos(theta);
	return (mat);
}
