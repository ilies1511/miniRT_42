#include <main.h>
#include <ft_engine.h>
#include <libft.h>

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
void	eng_intersc_ray_cylinder_caps(t_intersc_arr *intersecs, t_ray ray,
		t_cylinder *cylinder)
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

void	eng_intersc_ray_cylinder(t_intersc_arr *intersecs, t_ray ray,
		t_cylinder *cylinder)
{
	double	a;
	double	b;
	double	c;
	double	temp;
	double	disc;
	double	y0;
	double	y1;

	a = (ray.direct.x * ray.direct.x) + (ray.direct.z * ray.direct.z);
	if (eq_f(a, (EPSILON)))
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
