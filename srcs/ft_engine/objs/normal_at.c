#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

/*
	use case: formula to compute normal vector of transformed sphere
*/
t_vec	eng_compute_normal_sphere_post_trans(t_sphere *sphere, t_point world_point)
{
	t_point		object_point;
	t_point		object_normal;
	t_point		world_normal;
	t_sphere	transformed;

	eng_transform((t_obj *)sphere, (t_obj *)&transformed);
	object_point = mtx_mult_mt(sphere->base_obj.inverse, \
		world_point);
	object_normal = sub_t(object_point, new_point(0, 0, 0));
	world_normal = mtx_mult_mt(mtx_transpose(sphere->base_obj.inverse), \
		object_normal);
	world_normal.w = 0;
	return (norm(world_normal));
}

/*
	use case: unit circle sphere (sphere that was not tranformed yet)
*/
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
		// normal = compute_normal_sphere((t_sphere *)object, intersec_point);
		normal = eng_compute_normal_sphere_post_trans((t_sphere *)object, \
			intersec_point);
	}
	//else if (andere Types)
	else
	{
		ft_assert(0, __FILE__, __LINE__, "eng_normal_at: Wrong Input");
	}
	return (norm(normal));
}
