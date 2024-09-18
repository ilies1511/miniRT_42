#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

t_vec	compute_normal_sphere(t_sphere *sphere, t_point point)
{
	t_point	delta;
	t_vec	normal;

	delta = sub_t(point, sphere->origin);
	normal = new_vec(delta.x, delta.y, delta.z);
	return (normal);
}

t_vec	eng_normal_at(t_obj *object, t_point intersec_point)
{
	t_vec		normal;

	if (object->type == OBJ_SPHERE)
	{
		normal = compute_normal_sphere((t_sphere *)object, intersec_point);
		normal = norm(normal);
	}
	//else if (andere Types)
	else
	{
		ft_assert(0, __FILE__, __LINE__, "eng_normal_at: Wrong Input");
	}
	return (norm(normal));
}
