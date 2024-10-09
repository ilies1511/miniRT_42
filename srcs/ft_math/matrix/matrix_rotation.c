/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:47 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:48 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// aka pitch
t_matrix	mtx_rotation_x(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[1][1] = cos(theta);
	mat.m[2][1] = sin(theta);
	mat.m[1][2] = -sin(theta);
	mat.m[2][2] = cos(theta);
	return (mat);
}

// rotation on y-axis
// theta == 0 ->default
// front rotation right to left
// back rotation left to right
// aka yaw
t_matrix	mtx_rotation_y(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[0][0] = cos(theta);
	mat.m[2][0] = -sin(theta);
	mat.m[0][2] = sin(theta);
	mat.m[2][2] = cos(theta);
	return (mat);
}

// rotation on z-axis
// theta == 0 ->default
// clock wise roll
// aka roll
t_matrix	mtx_rotation_z(double theta)
{
	t_matrix	mat;

	mat = mtx_new_ident(MAT4X4);
	mat.m[0][0] = cos(theta);
	mat.m[0][1] = -sin(theta);
	mat.m[1][0] = sin(theta);
	mat.m[1][1] = cos(theta);
	return (mat);
}

t_matrix	mtx_rotation_axis_angle(t_vec axis, double angle)
{
	double		cos_a;
	double		sin_a;
	double		one_minus_cos_a;
	t_matrix	rot;

	cos_a = cos(angle);
	sin_a = sin(angle);
	one_minus_cos_a = 1.0 - cos_a;
	axis = norm(axis);
	rot = mtx_new_ident(MAT4X4);
	rot.m[0][0] = cos_a + axis.x * axis.x * one_minus_cos_a;
	rot.m[0][1] = axis.x * axis.y * one_minus_cos_a - axis.z * sin_a;
	rot.m[0][2] = axis.x * axis.z * one_minus_cos_a + axis.y * sin_a;
	rot.m[1][0] = axis.y * axis.x * one_minus_cos_a + axis.z * sin_a;
	rot.m[1][1] = cos_a + axis.y * axis.y * one_minus_cos_a;
	rot.m[1][2] = axis.y * axis.z * one_minus_cos_a - axis.x * sin_a;
	rot.m[2][0] = axis.z * axis.x * one_minus_cos_a - axis.y * sin_a;
	rot.m[2][1] = axis.z * axis.y * one_minus_cos_a + axis.x * sin_a;
	rot.m[2][2] = cos_a + axis.z * axis.z * one_minus_cos_a;
	return (rot);
}