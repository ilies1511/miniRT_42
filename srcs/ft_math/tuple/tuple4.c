#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

void	print_t(int fd, t_tuple t)
{
	(void)fd;
	fprintf(stdout, "x: %f\ny: %f\nz: %f\nw: %f\n", \
		t.x, t.y, t.z, t.w);
}

