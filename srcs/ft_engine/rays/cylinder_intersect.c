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
	result = (x * x) + (z * z) <= 1;
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

static void	swap_double(t_cylinder_norm *n)
{
	double	temp;

	temp = n->t0;
	n->t0 = n->t1;
	n->t1 = temp;
}

/*
	Init for varibales, that are used for cylinder
*/
static void	init_cylinder_norm(t_cylinder_norm *n)
{
	n->a = 0;
	n->b = 0;
	n->c = 0;
	n->disc = 0;
	n->y0 = 0;
	n->y1 = 0;
	n->sqrt_discriminant = 0;
	n->two_a = 0;
	n->t0 = 0;
	n->t1 = 0;
}

void	eng_intersc_ray_cylinder(t_intersc_arr *intersecs, t_ray ray,
			t_cylinder *cylinder)
{
	t_cylinder_norm	n;

	init_cylinder_norm(&n);
	n.a = (ray.direct.x * ray.direct.x) + (ray.direct.z * ray.direct.z);
	if (eq_f(n.a, (EPSILON)))
		return (eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder));
	n.b = 2 * ray.origin.x * ray.direct.x + 2 * ray.origin.z * ray.direct.z;
	n.c = (ray.origin.x * ray.origin.x) + (ray.origin.z * ray.origin.z) - 1;
	n.disc = (n.b * n.b) - (4 * n.a * n.c);
	if (n.disc < 0)
		return (eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder));
	n.sqrt_discriminant = sqrtl(n.disc);
	n.two_a = (2 * n.a);
	n.t0 = (-(n.b) - n.sqrt_discriminant) / n.two_a;
	n.t1 = (-(n.b) + n.sqrt_discriminant) / n.two_a;
	if (n.t0 > n.t1)
		swap_double(&n);
	n.y0 = ray.origin.y + n.t0 * ray.direct.y;
	if (cylinder->min < n.y0 && n.y0 < cylinder->max)
		eng_add_intersc(intersecs, (t_obj *)cylinder, n.t0);
	n.y1 = ray.origin.y + n.t1 * ray.direct.y;
	if (cylinder->min < n.y1 && n.y1 < cylinder->max)
		eng_add_intersc(intersecs, (t_obj *)cylinder, n.t1);
	eng_intersc_ray_cylinder_caps(intersecs, ray, cylinder);
}
