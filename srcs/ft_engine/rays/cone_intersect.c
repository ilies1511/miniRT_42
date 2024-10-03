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
	if (y < 0)
		y = -y;
	result = (x * x) + (z * z) <= y;
	return (result);
}

void	eng_intersc_ray_cone_caps(t_intersc_arr *intersecs, t_ray ray,
		t_cone *cone)
{
	double	t;
	double	t2;

	// printf("In eng_intersc_ray_cone_caps: PRE add: %d\n", intersecs->count);
	if (cone->closed == false)
		return ;
	t = (cone->min - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t, cone->max))
		eng_add_intersc(intersecs, (t_obj *)cone, t);
	//TODO: CHeck again
	if (intersecs->count % 2 == 0)
	{
		t2 = (cone->max - ray.origin.y) / ray.direct.y;
		if (check_cap_cone(ray, t2, cone->max))
		{
			intersecs->arr[intersecs->count - 2].obj = (t_obj *)&cone;
			intersecs->arr[intersecs->count - 2].t = t2;
		}
		return ;
	}
	// printf("In eng_intersc_ray_cone_caps: POST1 add: %d\n", intersecs->count);
	t2 = (cone->max - ray.origin.y) / ray.direct.y;
	if (check_cap_cone(ray, t2, cone->max))
		eng_add_intersc(intersecs, (t_obj *)cone, t2);
	// printf("In eng_intersc_ray_cone_caps: POST2 add: %d\n", intersecs->count);
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

static void	cal_disc_sqrt(t_cone_norm *n)
{
	if (!eq_f(n->disc, 0))
		n->sqrt_discriminant = sqrtl(n->disc);
	else
		n->sqrt_discriminant = 0;
}

static void	cal_abc(t_cone_norm *n, t_intersc_arr *intersecs, t_ray ray,
			t_cone *cone)
{
	n->a = (ray.direct.x * ray.direct.x) - (ray.direct.y * ray.direct.y) + \
			(ray.direct.z * ray.direct.z);
	n->b = (2 * ray.origin.x * ray.direct.x) - \
		(2 * ray.origin.y * ray.direct.y) + (2 * ray.origin.z * ray.direct.z);
	n->c = (ray.origin.x * ray.origin.x) - (ray.origin.y * ray.origin.y) + \
		(ray.origin.z * ray.origin.z);
	n->two_a = (2 * n->a);
}

static void	cal_intesects(t_cone_norm *n)
{
	if (!eq_f(n->a, 0))
	{
		n->t0 = (-n->b - n->sqrt_discriminant) / n->two_a;
		n->t1 = (-n->b + n->sqrt_discriminant) / n->two_a;
	}
	else if (eq_f(n->a, 0) && !eq_f(n->b, 0))
	{
		n->t0 = -n->c / (2 * n->b);
		n->t1 = n->t0;
		// n->t1 = INFINITY; // oder bool
	}
	else
		ft_assert(false, __FILE__, __LINE__, \
			"Impossible Case for Cone Intersection");
}

static void	add_intersects(t_cone_norm *n, t_intersc_arr *intersecs, t_ray ray,
			t_cone *cone)
{
	// printf("In add_intersects: PRE add Intersecs Count: %d\n", intersecs->count);
	if (n->t0 > n->t1)
		swap_double(&n);
	n->y0 = ray.origin.y + n->t0 * ray.direct.y;
	if (cone->min < n->y0 && n->y0 < cone->max)
		eng_add_intersc(intersecs, (t_obj *)cone, n->t0);
	// printf("In add_intersects: POST1 add Intersecs Count: %d\n", intersecs->count);
	n->y1 = ray.origin.y + n->t1 * ray.direct.y;
	if (cone->min < n->y1 && n->y1 < cone->max)
		eng_add_intersc(intersecs, (t_obj *)cone, n->t1);
	// printf("In add_intersects: POST2 add Intersecs Count: %d\n", intersecs->count);
	eng_intersc_ray_cone_caps(intersecs, ray, cone);
}

void	eng_intersc_ray_cone(t_intersc_arr *intersecs, t_ray ray,
			t_cone *cone)
{
	t_cone_norm	n;

	init_cone_norm(&n);
	cal_abc(&n, intersecs, ray, cone);
	if (eq_f(n.a, 0) && eq_f(n.b, 0))
		return (eng_intersc_ray_cone_caps(intersecs, ray, cone));
	n.disc = (n.b * n.b) - (4 * n.a * n.c);
	if (n.disc < 0 - EPSILON)
		return ;
	cal_disc_sqrt(&n);
	cal_intesects(&n);
	add_intersects(&n, intersecs, ray, cone);
}
