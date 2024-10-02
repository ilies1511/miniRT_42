#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>
#include <ft_reflection.h>

t_point	mult_p_scalar(t_point point, double scale)
{
	t_point	new;

	new.x = point.x * scale;
	new.y = point.y * scale;
	new.z = point.z * scale;
	return (new);
}

t_computation	eng_prepare_computation(t_intersc intersc, t_ray ray)
{
	t_computation	comp;

	ft_bzero(&comp, sizeof comp);
	comp.t = intersc.t;
	comp.obj = intersc.obj;
	comp.point = eng_ray_pos(ray, comp.t);
	comp.eye_v = negate_v(ray.direct);
	comp.normal_v = eng_normal_at(comp.obj, comp.point);
	if (dot_prod(comp.normal_v, comp.eye_v) < 0)
	{
		comp.inside = true;
		comp.normal_v = negate_v(comp.normal_v);
	}
	else
		comp.inside = false;
	comp.over_point = add_t(comp.point, mult_v(comp.normal_v, (EPSILON)));
	comp.reflection = ref_reflect(ray.direct, comp.normal_v);
	return (comp);
}
