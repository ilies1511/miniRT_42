#include <ft_engine.h>
#include <libft.h>

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
