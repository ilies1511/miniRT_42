#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

void	print_tuple(int fd, t_tuple t)
{
	ft_fprintf(fd, "x: %f\ny: %f\nz: %f\nw: %f\n",
			t.x, t.y, t.z, t.w);
}

