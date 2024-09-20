#include <ft_matrix.h>
#include <ft_tuple.h>
#include <libft.h>
#include <ft_floats.h>

int	test_mtx_scaling(void)
{
	t_matrix	m_trans;
	t_tuple		v_trans;
	t_tuple		v_soll;
	t_tuple		v_ist;
	t_tuple		p_trans;
	t_tuple		p_soll;
	t_tuple		p_ist;

	p_ist = new_point(-4, 6, 8);
	p_soll = new_point(-8, 18, 32);
	v_ist = new_vec(-4, 6, 8);
	v_soll = new_vec(-8, 18, 32);

	m_trans = mtx_scale(2, 3, 4);
	p_trans = mtx_mult_mt(m_trans, p_ist);
	v_trans = mtx_mult_mt(m_trans, v_ist);
	if (t_check_ifequal(p_trans, p_soll) \
		&& t_check_ifequal(v_trans, v_soll))
		return (1);
	else
		return (0);
}
