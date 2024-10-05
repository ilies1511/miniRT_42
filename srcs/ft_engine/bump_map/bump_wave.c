#include <ft_bump_map.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>


t_bump	*bump_wave(void)
{
	t_bump	*bump;

	bump = bump_new_bump();
	bump->type = BUMP_WAVE;
	return (bump);
}

t_vec	bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal)
{
	t_vec		z_axis;
	t_vec		rotation_axis;
	t_matrix	rotation_matrix;
	double		angle;

	z_axis = new_vec(0, 0, 1);
	if (eq_t(base_normal, z_axis))
	{
		//TODO: what to do here
		return (base_normal);
	}
	rotation_axis = cross_prod(base_normal, z_axis);
	// angle = sin(point.z);

	/*
	2pi - 1.75 pi
	1.75pi - 2pi
	0pi-0.25pi
	0.25pi-0pi
	*/

	angle = fmod();
	rotation_matrix = mtx_rotation_axis_angle(rotation_axis, angle);
	return (mtx_mult_mt(rotation_matrix, base_normal));
	(void)bump;
}

