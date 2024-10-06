#include <main.h>
#include <ft_engine.h>
#include <libft.h>

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

	init_cone_norm(&n);
	cal_abc(&n, ray);
	if (eq_f(n.a, 0) && eq_f(n.b, 0))
		return ;
		// return (eng_intersc_ray_cone_caps(intersecs, ray, cone));
	n.disc = (n.b * n.b) - (4 * n.a * n.c);
	if (n.disc < 0 - EPSILON)
		return ;
	cal_disc_sqrt(&n);
	cal_intesects(&n);
	add_intersects(&n, intersecs, ray, cone);
}
