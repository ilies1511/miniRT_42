#include <ft_engine.h>

// returns the index of the hit intersection
// returns -1 if there was no hit
t_intersc	*eng_ray_hit(void)
{
	size_t			i;
	t_intersc_arr	*interscs;

	interscs = eng_get_intersc();

	i = 0;
	while (i < interscs->count && interscs->arr[i].t < 0)
		i++;
	if (i < interscs->count)
		return (interscs->arr + i);
	return (NULL);
}
