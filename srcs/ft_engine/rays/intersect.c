#include <main.h>
#include <ft_engine.h>

// time in terms of how many direction vectors of the ray
t_point	eng_ray_pos(t_ray ray, float time)
{
	t_point	pos;

	pos = mult_v(ray.direct, time);
	pos = add_t(pos, ray.origin);
	return (pos);
}


