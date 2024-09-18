#include <ft_engine.h>
#include <ft_tuple.h>

bool	eng_eq_ray(t_ray r1, t_ray r2)
{
	return (eq_t(r1.origin, r2.origin) && eq_t(r1.direct, r2.direct));
}
