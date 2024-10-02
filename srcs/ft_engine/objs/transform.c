#include <libft.h>
#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

// tmp var in case in == ret
static void	transform_ray(t_ray *in, t_ray *ret)
{
	t_ray	tmp;

	tmp = eng_new_ray(in->origin, in->direct);
	tmp.origin = mtx_mult_mt(in->base_obj.transform, in->origin);
	tmp.direct = mtx_mult_mt(in->base_obj.transform, in->direct);
	*ret = tmp;
}

static void	transform_sphere(t_sphere *in, t_sphere *ret)
{
	*ret = eng_new_sphere();
	ret->origin = mtx_mult_mt(in->base_obj.transform, in->origin);
}

void	eng_transform(t_obj *in, t_obj *ret)
{
	if (in->type == OBJ_RAY)
		transform_ray((t_ray *)in, (t_ray *)ret);
	else if (in->type == OBJ_SPHERE)
		transform_sphere((t_sphere *)in, (t_sphere *)ret);
	else
		ft_assert(0, __FILE__, __LINE__, "Error: eng_transform: Invalid type");
}
