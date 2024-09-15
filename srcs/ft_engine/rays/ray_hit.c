#include <ft_engine.h>

// returns the index of the hit intersection
// returns -1 if there was no hit
int	eng_ray_hit(t_ray *ray)
{
	int	i;
	int	count;

	count = ray->interscs_count;
	i = 0;
	while (ray->interscs[i].t < 0 && i < count)
		i++;
	if (i < count)
		return (i);
	return (-1);
}
