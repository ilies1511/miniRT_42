#include <ft_engine.h>
#include <main.h>
#include <libft.h>

// if ray.intersec_coint == -1 -> malloc err
t_ray	eng_new_ray(t_point origin, t_vec direct)
{
	t_ray	ray;

	ft_assert(is_point(origin), __FILE__, __LINE__, "Error: eng_new_ray: \
			origin is not a point");
	ft_assert(is_vec(direct), __FILE__, __LINE__, "Error: eng_new_ray: \
			direct is not a vec");
	ray.base_obj = eng_new_obj();
	ray.base_obj.type = OBJ_RAY;
	ray.origin = origin;
	ray.direct = direct;
	return (ray);
}

t_obj	eng_new_obj(void)
{
	t_obj	obj;

	obj.transform = mtx_new_ident(MAT4X4);
	obj.inverse = mtx_new_ident(MAT4X4);
	obj.type = OBJ_DEFAULT;
	obj.material = eng_new_material();
	return (obj);
}

t_sphere	eng_new_glass_sphere(void)
{
	t_sphere	sph;

	sph = eng_new_sphere();
	sph.base_obj.material.transparency = 1.0;
	sph.base_obj.material.refractive_index = 1.5;
	return (sph);
}

t_sphere	eng_new_sphere(void)
{
	t_sphere	sph;

	sph.base_obj = eng_new_obj();
	sph.base_obj.type = OBJ_SPHERE;
	sph.rad = 1;
	sph.origin = new_point(0, 0, 0);
	return (sph);
}

t_plane	eng_new_plane(void)
{
	t_plane	plane;

	plane.base_obj = eng_new_obj();
	plane.base_obj.type = OBJ_PLANE;
	return (plane);
}

t_cylinder	eng_new_cylinder(void)
{
	t_cylinder	cylinder;

	cylinder.base_obj = eng_new_obj();
	cylinder.base_obj.type = OBJ_CYLINDER;
	cylinder.rad = 1;
	cylinder.max = INFINITY;
	cylinder.min = -INFINITY;
	cylinder.closed = false;
	cylinder.origin = new_point(0, 0, 0);
	return (cylinder);
}
