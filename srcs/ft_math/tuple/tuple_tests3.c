#include <ft_tuple.h>
#include <ft_floats.h>
#include <stdlib.h>

float	len_v(t_vec v);
t_vec	norm(t_vec v);
float	dot_prod(t_vec a, t_vec b);
t_vec	cross_prod(t_vec a, t_vec b);
t_tuple	get_rdm_tuple(void)
{
	t_tuple	t;

	t.x = ((float)rand()) / rand();
	t.y = ((float)rand()) / rand();
	t.z = ((float)rand()) / rand();
	t.w = ((float)rand()) / rand();
	return (t);
}

