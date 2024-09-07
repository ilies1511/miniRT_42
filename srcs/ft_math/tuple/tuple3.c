#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

float	len_v(t_vec t);
t_tuple	norm(t_vec t);
float	dot_prod(t_vec a, t_vec b);
t_vec	cross_prod(t_vec a, t_vec b);

void	print_tuple(int fd, t_tuple t)
{
	ft_fprintf(fd, "x: %f\ny: %f\nz: %f\nw: %f\n",
			t.x, t.y, t.z, t.w);
}

