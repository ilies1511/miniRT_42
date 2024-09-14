#include <main.h>
#include <ft_engine.h>
#include <libft.h>

// time in terms of how many direction vectors of the ray
t_point	eng_ray_pos(t_ray ray, float time)
{
	t_point	pos;

	pos = mult_v(ray.direct, time);
	pos = add_t(pos, ray.origin);
	return (pos);
}

// returns the intersection count
// returns -1 on malloc error
// overwrites *ret_instersects with a new dynamic array
// this array has to be later on freed by calling dyn_arr_free() on it
int	eng_intersects_ray_sphere(t_ray ray, t_sphere sph, float **ret_intersects)
{
	int	count;
	float	time;

	*ret_intersects = dyn_arr_init(sizeof (float), 4);
	if (!*ret_intersects)
	{
		ft_fprintf(2, "Error: malloc failed\n");
		return (-1);
	}
	count = 0;
	dyn_arr_add_save((void **)ret_intersects, &time, count++);

	return (count);
}

