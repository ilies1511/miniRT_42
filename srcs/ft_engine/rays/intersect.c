#include <main.h>
#include <ft_engine.h>
#include <libft.h>

// proof in sphere_proof.md
// simplified with the assumtion of unit spheres in object space
static void	eng_intersc_ray_sphere(t_intersc_arr *interscs, t_ray ray,
		t_sphere *sph)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;

	ray.origin.w = 0;
	a = dot_prod(ray.direct, ray.direct);
	b = 2 * dot_prod(ray.origin, ray.direct);
	c = dot_prod(ray.origin, ray.origin) - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	sqrt_discriminant = sqrt(discriminant);
	eng_add_intersc(interscs, (t_obj *)sph, (-b + sqrt_discriminant) / (2 * a));
	eng_add_intersc(interscs, (t_obj *)sph, (-b - sqrt_discriminant) / (2 * a));
}

// assumes the plane to be the xz plane (normal == 0, 1, 0) at y = 0
static void	eng_intersc_ray_plane(t_intersc_arr *interscs, t_ray ray,
	t_plane *plane)
{
	double	t;

	if (fabsl(ray.direct.y) < (EPSILON))
		return ;
	t = -ray.origin.y / ray.direct.y;
	eng_add_intersc(interscs, (t_obj *)plane, t);
}

void	eng_intersc_ray(t_intersc_arr *interscs, t_ray ray, t_obj *obj)
{
	ray.base_obj.transform = obj->inverse;
	eng_transform((t_obj *)&ray, (t_obj *)&ray);
	if (obj->type == OBJ_SPHERE)
		eng_intersc_ray_sphere(interscs, ray, (t_sphere *)obj);
	else if (obj->type == OBJ_PLANE)
		eng_intersc_ray_plane(interscs, ray, (t_plane *)obj);
	else if (obj->type == OBJ_CYLINDER)
		eng_intersc_ray_cylinder(interscs, ray, (t_cylinder *)obj);
	else if (obj->type == OBJ_CONE)
		eng_intersc_ray_cone(interscs, ray, (t_cone *)obj);
	else
		ft_assert(0, __FILE__, __LINE__, "eng_intersc_ray: invalid obj type");
}

void	eng_ray_intersc_world(t_ray ray, t_world world, t_intersc_arr *interscs)
{
	size_t	i;

	i = 0;
	while (i < world.obj_count)
	{
		eng_intersc_ray(interscs, ray, world.objs[i]);
		i++;
	}
	eng_sort_intersc(interscs);
}
