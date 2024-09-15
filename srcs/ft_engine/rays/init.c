#include <ft_engine.h>
#include <main.h>
#include <libft.h>

// if ray.intersec_coint == -1 -> malloc err
t_ray	eng_new_ray(t_point origin, t_vec direct)
{
	t_ray	ray;

	ft_assert(is_point(origin), __FILE__, __LINE__, "Error: eng_new_ray: \
			origin is not a point");
	ft_assert(is_vec(direct), __FILE__, __LINE__, "Error: eng_new_ray: \
			direct is not a vec");
	ray.origin = origin;
	ray.direct = direct;
	return (ray);
}

t_sphere	eng_new_sphere(void)
{
	t_sphere	sph;

	sph.rad = 1;
	sph.origin = new_point(0, 0, 0);
	return (sph);
}
