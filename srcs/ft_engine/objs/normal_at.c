#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

/*
	use case: unit circle sphere (sphere that was not tranformed yet)
*/
t_vec	compute_normal_sphere(t_point object_point)
{
	t_point		object_normal;

	object_normal = sub_t(object_point, new_point(0, 0, 0));
	return (object_normal);
}

t_vec	compute_normal_plane(t_point object_point)
{
	(void) object_point;
	return (new_vec(0, 1, 0));
}

static t_vec	normal_at_iterate_types(t_obj *object, t_point point_obj_space)
{
	if (object->type == OBJ_SPHERE)
		return(compute_normal_sphere(point_obj_space));
	else if (object->type == OBJ_PLANE)
		return(compute_normal_plane(point_obj_space));
	//TODO:
	//else if (object->type == OBJ_CYLINDER)
	//	return(compute_normal_cylinder(point_obj_space));
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
