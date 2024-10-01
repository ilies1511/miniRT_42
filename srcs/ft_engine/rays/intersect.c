#include <main.h>
#include <ft_engine.h>
#include <libft.h>

static bool	swap_intersc(void *a, void *b)
{
	return (((t_intersc *)a)->t > ((t_intersc *)b)->t);
}

void	eng_sort_intersc(t_intersc_arr *interscs)
{
	ft_sort(interscs->arr, sizeof(t_intersc), interscs->count, swap_intersc);
}

t_intersc	eng_add_intersc(t_intersc_arr *interscs, t_obj *obj, double t)
{
	t_intersc		intersc;

	intersc.t = t;
	intersc.obj = obj;
	if (!interscs->arr)
		*interscs = eng_new_intersc_arr();
	dyn_arr_add_save((void **)(&interscs->arr), &intersc, interscs->count++);
	return (intersc);
}

t_intersc_arr	eng_new_intersc_arr(void)
{
	t_intersc_arr	arr;

	arr.arr = dyn_arr_init(sizeof(t_intersc), 0);
	if (!arr.arr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	arr.count = 0;
	return (arr);
}


/*
//Wikipedia line sphere intersection step by step:
point px: intersection point
double t: scalar for ray->direct to reach the intersection point and
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
// double	dot_direct = dot(ray->dircet, ray.direct)
// double	dot_diff_direct = dot(ori_diff, ray->direct);
// double	dot_diff = dot(ori_diff, ori_diff);
// a = dot_direct
// b =  2 *dot_diff_direct
// c = dot_diff - sph.rad^2
// t = (-b +- sqrt(b^2 - 4 * a * c)) / 2a
// double sqr_dot_diff_direct = dot_direct * dot_direct
-> t = -2*dot_diff_direct +- sqrt(sqr_dot_diff_direct - 4 * dot_direct * (dot_diff - sph.rad^2)) / (2 * dot_direct)
*/
// can be simplyfied by making assumtions like unit vectors, that the sphere
// is in the orgin, or has a radius of 1
// this function should always fork for spheres so I think we can simplyfy
// later when we can make some assumptions we can simplify
static void	eng_intersc_ray_sphere(t_intersc_arr *interscs, t_ray ray, t_sphere *sph)
{
	t_vec	ori_diff = sub_t(ray.origin, sph->origin);
	double	dot_direct = dot_prod(ray.direct, ray.direct);
	double	dot_diff_direct = dot_prod(ori_diff, ray.direct);
	double	dot_diff = dot_prod(ori_diff, ori_diff);
	double	rad_sqr = sph->rad * sph->rad;
	double	a = dot_direct;
	double	b = 2 * dot_diff_direct;
	double	c = dot_diff - rad_sqr;
	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	double	sqrt_discriminant = sqrt(discriminant);
	double	t1 = (-b + sqrt_discriminant) / (2 * a);
	double	t2 = (-b - sqrt_discriminant) / (2 * a);
	eng_add_intersc(interscs, (t_obj *)sph, t1);
	eng_add_intersc(interscs, (t_obj *)sph, t2);
}

// assumes the plane to be the xz plane (normal == 0, 1, 0) at y = 0
static void	eng_intersc_ray_plane(t_intersc_arr *interscs, t_ray ray,
	t_plane *plane)
{
	double	t;

	if (fabsl(ray.direct.y) < EPSILON)
		return ;
	t = -ray.origin.y / ray.direct.y;
	eng_add_intersc(interscs, (t_obj *)plane, t);
}
static bool	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;
	bool	result;

	x = ray.origin.x + t * ray.direct.x;
	z = ray.origin.z + t * ray.direct.z;
	result = (x * x ) + (z * z) <= 1;
	return (result);
}
void	eng_intersc_ray_cylinder_caps(t_intersc_arr *intersecs, t_ray ray, t_cylinder *cylinder)
{
	double	t;
	double	t2;

	if (cylinder->closed == false)
		return ;
	t = (cylinder->min - ray.origin.y) / ray.direct.y;
	if (check_cap(ray, t))
		eng_add_intersc(intersecs, (t_obj *)cylinder, t);
	t2 = (cylinder->max - ray.origin.y) / ray.direct.y;
	if (check_cap(ray, t2))
		eng_add_intersc(intersecs, (t_obj *)cylinder, t2);
}

void	eng_intersc_ray_cylinder(t_intersc_arr *intersecs, t_ray ray, t_cylinder *cylinder)
{
	double	a;
	double	b;
	double	c;
	double	temp;
	double	disc;
	double	y0;
	double	y1;

	a = (ray.direct.x * ray.direct.x) + (ray.direct.z * ray.direct.z);
	if (eq_f(a, EPSILON))
		return (eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder));
	b = 2 * ray.origin.x * ray.direct.x + 2 * ray.origin.z * ray.direct.z;
	c = (ray.origin.x * ray.origin.x) + (ray.origin.z * ray.origin.z) - 1;
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return (eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder));
	double	sqrt_discriminant = sqrtl(disc);
	double	two_a = (2 * a);
	double	t0 = (-b - sqrt_discriminant) / two_a;
	double	t1 = (-b + sqrt_discriminant) / two_a;
	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	y0 = ray.origin.y + t0 * ray.direct.y;
	if (cylinder->min < y0 && y0 < cylinder->max)
		eng_add_intersc(intersecs, (t_obj *)cylinder, t0);
	y1 = ray.origin.y + t1 * ray.direct.y;
	if (cylinder->min < y1 && y1 < cylinder->max)
		eng_add_intersc(intersecs, (t_obj *)cylinder, t1);
	// eng_add_intersc(intersecs, cylinder, 1);
	eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder);
}

void	eng_intersc_ray(t_intersc_arr *interscs, t_ray ray, t_obj *obj)
{
	ray.base_obj.transform = obj->inverse;
	eng_transform((t_obj *)&ray, (t_obj *)&ray);
	if (obj->type == OBJ_SPHERE)
		eng_intersc_ray_sphere(interscs, ray, (t_sphere *)obj);
	else if (obj->type == OBJ_PLANE)
		eng_intersc_ray_plane(interscs, ray, (t_plane *)obj);
	//TODO: Add Cylinder
	else if (obj->type == OBJ_CYLINDER)
		eng_intersc_ray_cylinder(interscs, ray, (t_cylinder *)obj);
	else
		ft_assert(0, __FILE__, __LINE__, "eng_intersc_ray: invalid obj type");
}

void	eng_ray_intersc_world(t_ray ray, t_world world, t_intersc_arr *interscs)
{
	size_t	i;

	i = 0;
	while (i < world.obj_count)
	{
 		t_obj *obj = world.objs[i];
 		eng_intersc_ray(interscs, ray, obj);
		i++;
 	}
	eng_sort_intersc(interscs);
}


