#include <ft_engine.h>
#include <main.h>


t_matrix	sc_transforme_view(t_point from, t_point to, t_vec up)
{
	t_vec		forward;
	t_vec		left;
	t_vec		true_up;
	t_point		delta;
	t_matrix	orientation;
	t_matrix	result;

	delta = sub_t(to, from);
	forward = norm(new_vec(delta.x, delta.y, delta.z));
	left = cross_prod(forward, norm(up));
	true_up = cross_prod(left, forward);
	orientation = mtx_new_ident(MAT4X4);
	orientation.m[0][0] = left.x;
	orientation.m[0][1] = left.y;
	orientation.m[0][2] = left.z;
	orientation.m[1][0] = true_up.x;
	orientation.m[1][1] = true_up.y;
	orientation.m[1][2] = true_up.z;
	orientation.m[2][0] = -forward.x;
	orientation.m[2][1] = -forward.y;
	orientation.m[2][2] = -forward.z;
	result = mtx_mult_mm(orientation, mtx_translate(-from.x, -from.y, -from.z));
	return (result);
}
