#include <ft_matrix.h>
#include <ft_tuple.h>
#include <libft.h>
#include <ft_floats.h>

int	t_check_ifequal(t_tuple a, t_tuple b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w)
		return (1);
	return (0);
}

int	p_compareifequal(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	return (0);
}

/*
	TODO: FIX
	funktionsunfaehig, falsche Funktion: print_t(1, transformed_point);

	Translation affects Points, however they shoul affect vectors
*/
int	test_matrix_translation(void)
{
	t_tuple		p_ist;
	t_tuple		transformed_point;
	t_point		params;
	t_point		p_soll;
	t_tuple		v_ist;
	t_vec		v_soll;
	t_vec		v_trans;
	t_matrix	m_transformed;

	p_soll = new_point(2, 1, 7);
	p_ist = new_point(-3, 4, 5);
	v_ist = new_vec(-3, 4, 5);
	v_soll = new_vec(-3, 4, 5);
	params = new_point(5, -3, 2);
	m_transformed = mtx_translation_izi(params);
	// m_transformed = mtx_translation(5, -3, 2);
	transformed_point = mtx_mult_mt(m_transformed, p_ist);
	printf("x: %f\ty: %f\tz: %f\tw: %f\n", transformed_point.x, \
	transformed_point.y, transformed_point.z, \
	transformed_point.w);
	v_trans = mtx_mult_mt(m_transformed, v_ist);
	printf("x: %f\ty: %f\tz: %f\tw: %f\n", v_trans.x, \
	v_trans.y, v_trans.z, \
	v_trans.w);
	if (p_compareifequal(transformed_point, p_soll) \
		&& t_check_ifequal(v_trans, v_soll))
		return (1);
	else
		return (0);
}
