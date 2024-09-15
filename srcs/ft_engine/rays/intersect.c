#include <main.h>
#include <ft_engine.h>
#include <libft.h>

// time in terms of how many direction vectors of the ray
t_point	eng_ray_pos(t_ray ray, float time)
{
	t_point	pos;

	pos = mult_v(ray.direct, time);
	pos = add_t(pos, ray.origin);
	return (pos);
}

bool	swap_intersects(void *a, void *b)
{
	return (((t_intersection *)a)->t > ((t_intersection *)b)->t);
}

// returns -1 on malloc error
// can be simplyfied by making assumtions like unit vectors, that the sphere
// is in the orgin, or has a radius of 1
// this function should always fork for spheres so I think we can simplyfy
// later when we can make some assumptions we can simplify
int	eng_intersects_ray_sphere(t_ray *ray, t_sphere *sph)
{
	/*
	//Wikipedia line sphere intersection step by step:
	point px: intersection point
	float t: scalar for ray->direct to reach the intersection point and
		the var we want

	// ray formular with px beeing a point on the ray
	1:	ray->origin + t * ray.direct = px
	// sphere formular with px beeing on the surface of the sphere
	2:	|| px - sph.origin || = sph.rad
	// substitude px in 2 by 1 since px should meet both formulars
	-> || (ray->origin + t * ray.direct) - sph.origin || = sph.rad
	// start solving for t:
	-> || ray->origin - sph.origin + t * ray.direct  || = sph.rad
	// vec ori_diff = ray->origin - sph.origin
	-> || ori_diff + t * ray->direct  || = sph.rad
	-> sqr(dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct)) = sph.rad
	// square both sides to get rid of sqrt
	->dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct) = sph.rad^2
	//distributive law
	->dot(ori_diff, ori_diff + t * ray->direct) + dot(t * ray.direct, ori_diff + t * ray.direct) = sph.rad^2
	//distributive law
	->dot(ori_diff, ori_diff) + dot(ori_diff, t * ray->direct) + dot(t * ray.direct, ori_diff) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
	->dot(ori_diff, ori_diff) + 2 * dot(ori_diff, t * ray->direct) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
	->dot(ori_diff, ori_diff) + 2 * t * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) = sph.rad^2
	// form quadratic formular
	//at^2 + tb + c = 0
	//-sph.rad^2
	->dot(ori_diff, ori_diff) + t * 2 * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) - sph.rad^2 = 0
	->t^2 * dot(ray->direct, ray.direct) + 2 * t * dot(ori_diff, ray.direct) + dot(ori_diff, ori_diff) - sph.rad^2 = 0
	// float	dot_direct = dot(ray->dircet, ray.direct)
	// float	dot_diff_direct = dot(ori_diff, ray->direct);
	// float	dot_diff = dot(ori_diff, ori_diff);
	// a = dot_direct
	// b =  2 *dot_diff_direct
	// c = dot_diff - sph.rad^2
	// t = (-b +- sqrt(b^2 - 4 * a * c)) / 2a
	// float sqr_dot_diff_direct = dot_direct * dot_direct
	-> t = -2*dot_diff_direct +- sqrt(sqr_dot_diff_direct - 4 * dot_direct * (dot_diff - sph.rad^2)) / (2 * dot_direct)
	*/
	t_vec	ori_diff = sub_t(ray->origin, sph->origin);
	float	dot_direct = dot_prod(ray->direct, ray->direct);
	float	dot_diff_direct = dot_prod(ori_diff, ray->direct);
	float	dot_diff = dot_prod(ori_diff, ori_diff);
	float	rad_sqr = sph->rad * sph->rad;
	float	a = dot_direct;
	float	b = 2 * dot_diff_direct;
	float	c = dot_diff - rad_sqr;
	float	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (1);
	float	sqrt_discriminant = sqrt(discriminant);
	float	t1 = (-b + sqrt_discriminant) / (2 * a);
	float	t2 = (-b - sqrt_discriminant) / (2 * a);
	t_intersection	intersect;
	intersect.obj = sph;
	intersect.type = OB_SPHERE;
	intersect.t = t1;
	dyn_arr_add_save((void **)(&(ray->intersects)), &intersect, (ray->intersec_count)++);
	if (!ray->intersects)
	{
		fprintf(stderr, "malloc err\n");
		return (-1);
	}
	intersect.t = t2;
	dyn_arr_add_save((void **)(&(ray->intersects)), &intersect, (ray->intersec_count)++);
	if (!ray->intersects)
	{
		fprintf(stderr, "malloc err\n");
		return (-1);
	}
	ft_sort(ray->intersects, sizeof ray->intersects[0], ray->intersec_count, swap_intersects);
	return (1);
}

