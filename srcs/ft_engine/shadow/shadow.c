#include <ft_engine.h>
#include <main.h>

bool	eng_is_shadowed(t_world world, t_point point)
{
	t_vec			v;
	t_vec			direction;
	t_point			delta;
	float			distance;
	t_ray			ray;
	t_intersc_arr	intersecs;
	t_intersc		*intersec;

	delta = sub_t(world.lights->origin, point);
	v = new_vec(delta.x, delta.y, delta.z);
	distance = len_v(v);
	direction = norm(v);
	ray = eng_new_ray(point, direction);
	intersecs = eng_new_intersc_arr();
	eng_ray_intersc_world(ray, world, &intersecs);
	intersec = eng_ray_hit(&intersecs);
	if (intersec && intersec->t < distance)
		return (eng_free_intersc_arr(&intersecs), true);
	else
		return (eng_free_intersc_arr(&intersecs), false);
}
