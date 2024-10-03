#include <main.h>
#include <ft_engine.h>
#include <libft.h>

static void	swap_double(t_cone_norm *n)
{
	double	temp;

	temp = n->t0;
	n->t0 = n->t1;
	n->t1 = temp;
}

static bool	check_cap_cone(t_ray ray, double t, double y)
{
	double	x;
	double	z;
	bool	result;

	x = ray.origin.x + t * ray.direct.x;
	z = ray.origin.z + t * ray.direct.z;
	result = (x * x) + (z * z) <= y;
	return (result);
}

void	eng_intersc_ray_cone_caps(t_intersc_arr *intersecs, t_ray ray,
		t_cone *cone)
{
	double	t;
	double	t2;

	if (cone->closed == false)
		return ;
	t = (cone->min - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t, cone->max))
		eng_add_intersc(intersecs, (t_obj *)cone, t);
	t2 = (cone->max - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t2, cone->max))
		eng_add_intersc(intersecs, (t_obj *)cone, t2);
}

/*
	Init for varibales, that are used for cone
*/
static void	init_cone_norm(t_cone_norm *n)
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

void	eng_intersc_ray_cone(t_intersc_arr *intersecs, t_ray ray,
			t_cone *cone)
{
	t_cone_norm	n;
	bool		flag;

	flag = false;
	init_cone_norm(&n);
	n.a = (ray.direct.x * ray.direct.x) - (ray.direct.y * ray.direct.y) + \
			(ray.direct.z * ray.direct.z);
	if (eq_f(n.a, (EPSILON)))
		return (eng_intersc_ray_cone_caps(intersecs, ray, cone));
	n.b = (2 * ray.origin.x * ray.direct.x) - (2 * ray.origin.y * ray.direct.y) + \
		(2 * ray.origin.z * ray.direct.z);
	n.c = (ray.origin.x * ray.origin.x) - (ray.origin.y * ray.origin.y) \
		+ (ray.origin.z * ray.origin.z);
	//Disc muss fuer Cones raus
	n.disc = (n.b * n.b) - (4 * n.a * n.c);
	if (n.disc < 0)
		return ;
	// return (eng_intersc_ray_cone_caps(intersecs, ray, cone));
	//TODO: 2CHECK if correct spot
	if (eq_f(n.a, EPSILON) && !eq_f(n.b, EPSILON))
	{
		flag = true;
		n.t0 = -(n.c) / 2 * n.b;
	}
	n.sqrt_discriminant = sqrtl(n.disc);
	n.two_a = (2 * n.a);
	if (!flag)
	{
		n.t0 = (-(n.b) - n.sqrt_discriminant) / n.two_a;
		n.t1 = (-(n.b) + n.sqrt_discriminant) / n.two_a;
	}
	// n.t0 = (-(n.b) - n.sqrt_discriminant) / n.two_a;
	// n.t1 = (-(n.b) + n.sqrt_discriminant) / n.two_a;
	if (n.t0 > n.t1)
		swap_double(&n);
	n.y0 = ray.origin.y + n.t0 * ray.direct.y;
	if (cone->min < n.y0 && n.y0 < cone->max)
		eng_add_intersc(intersecs, (t_obj *)cone, n.t0);
	n.y1 = ray.origin.y + n.t1 * ray.direct.y;
	if (cone->min < n.y1 && n.y1 < cone->max)
		eng_add_intersc(intersecs, (t_obj *)cone, n.t1);
	// eng_intersc_ray_cone_caps(intersecs, ray, cone);
}
