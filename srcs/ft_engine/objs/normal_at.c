#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

/*
	use case: unit circle sphere (sphere that was not tranformed yet)
*/
t_vec	comput_normal_sphere(t_sphere *sphere, t_point object_point)
{
	t_point		object_normal;

	object_normal = sub_t(object_point, new_point(0, 0, 0));
	return (object_normal);
}

static t_vec	normal_at_iterate_types(t_obj *object, t_point point_obj_space)
{
	if (object->type == OBJ_SPHERE)
		return(comput_normal_sphere((t_sphere *)object, point_obj_space));
	//else if (andere Types)
	else
	{
		ft_assert(0, __FILE__, __LINE__, "eng_normal_at: Wrong Input");
		__builtin_unreachable();
	}
}

t_vec	eng_normal_at(t_obj *object, t_point intersec_point)
{
	t_point		point_obj_space;
	t_vec		normal_obj_space;
	t_vec		normal_world_space;

	point_obj_space = mtx_mult_mt(object->inverse, intersec_point);
	normal_obj_space = normal_at_iterate_types(object, point_obj_space);
	normal_world_space = mtx_mult_mt(mtx_transpose(object->inverse), \
		normal_obj_space);
	normal_world_space.w = 0;
	return (norm(normal_world_space));
}
