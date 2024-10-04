#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>

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

t_vec	compute_normal_cylinder(t_cylinder *cylinder, t_point object_point)
{
	double	distance;

	ft_assert(cylinder->base_obj.type == OBJ_CYLINDER, __FILE__, __LINE__, "wtf");
	distance = (object_point.x * object_point.x) + (object_point.z
			* object_point.z);
	if (distance < 1 && object_point.y >= cylinder->max - (EPSILON))
		return (new_vec(0, 1, 0));
	else if (distance < 1 && object_point.y <= cylinder->min + (EPSILON))
		return (new_vec(0, -1, 0));
	else
		return (new_vec(object_point.x, 0, object_point.z));
}

t_vec	compute_normal_cone(t_cone *cone, t_point object_point)
{
	double	distance;
	double	y;

	return (new_vec(0, 1, 0));
	////TODO: 2fix casea
	//if (eq_t(object_point, new_point(0, 0, 0)))
	//	return (norm(new_vec(0, 1, 0)));
	//distance = (object_point.x * object_point.x) + \
	//	(object_point.z * object_point.z);
	//////TODO: something here causes undefiend behaivior where depending of the compiler flags diffrent tests start failing
	////if (distance < 1 && object_point.y >= cone->max - (EPSILON))
	////	return (new_vec(0, 1, 0));
	////else if (distance < 1 && object_point.y <= cone->min + (EPSILON))
	////	return (new_vec(0, -1, 0));
	////else
	//{
	//	y = sqrt((object_point.x * object_point.x) \
	//		+ (object_point.z * object_point.z));
	//	if (object_point.y > 0)
	//		y = -y;
	//	return (new_vec(object_point.x, y, object_point.z));
	//}
}

static t_vec	normal_at_iterate_types(t_obj *object, t_point point_obj_space)
{
	if (object->type == OBJ_SPHERE)
		return (compute_normal_sphere(point_obj_space));
	else if (object->type == OBJ_PLANE)
		return (compute_normal_plane(point_obj_space));
	else if (object->type == OBJ_CYLINDER)
		return (compute_normal_cylinder((t_cylinder *)object, point_obj_space));
	else if (object->type == OBJ_CONE)
		return (compute_normal_cone((t_cone *)object, point_obj_space));
	else
	{
		ft_assert(0, __FILE__, __LINE__, "eng_normal_at: Wrong Input");
		__builtin_unreachable();
	}
}

t_vec	eng_normal_at(t_obj *restrict object, t_point intersec_point)
{
	t_point		point_obj_space;
	t_vec		normal_obj_space;
	t_vec		normal_world_space;

	printf("%u\n", object->type);
	point_obj_space = mtx_mult_mt(object->inverse, intersec_point);
	normal_obj_space = normal_at_iterate_types(object, point_obj_space);
	normal_world_space = mtx_mult_mt(mtx_transpose(object->inverse), \
		normal_obj_space);
	normal_world_space.w = 0;
	return (norm(normal_world_space));
}
