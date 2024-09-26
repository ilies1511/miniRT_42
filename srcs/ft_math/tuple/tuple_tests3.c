#include <ft_tuple.h>
#include <ft_floats.h>
#include <stdlib.h>

double	len_v(t_vec v);
t_vec	norm(t_vec v);
double	dot_prod(t_vec a, t_vec b);
t_vec	cross_prod(t_vec a, t_vec b);
t_tuple	get_rdm_tuple(void)
{
	t_tuple	t;

	t.x = ((double)rand()) / rand();
	t.y = ((double)rand()) / rand();
	t.z = ((double)rand()) / rand();
	t.w = ((double)rand()) / rand();
	return (t);
}

