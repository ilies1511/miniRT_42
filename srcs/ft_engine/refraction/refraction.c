#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>

/*
	Init for varibales, that are used for refracted color
*/
static void	init_norm(t_refracted_color_norm *n)
{
	n->color = new_fcolor(0, 0, 0, 1);
	n->cos_val = 0.0;
	n->cos_vecs = 0.0;
	n->direct = new_vec(0, 0, 0);
	n->ratio = 0.0;
	n->sin_sqr = 0.0;
}

/* uses Snell's Law:
 * sin(incoming) / sin(out) = n2 / n1
*/
t_fcolor	refracted_color(t_world world, t_computation comp, size_t remaining)
{
	t_refracted_color_norm	n;

	init_norm(&n);
	if (eq_f(comp.obj->material.transparency, 0) || !remaining)
		return (fcolor_black());
	n.cos_vecs = dot_prod(comp.eye_v, comp.normal_v);
	n.ratio = comp.n1 / comp.n2;
	n.sin_sqr = n.ratio * n.ratio * (1 - n.cos_vecs * n.cos_vecs);
	if (n.sin_sqr > 1)
		return (fcolor_black());
	n.cos_val = sqrt(1.0 - n.sin_sqr);
	n.direct = mult_v(comp.normal_v, n.ratio * n.cos_vecs - n.cos_val);
	n.direct = sub_t(n.direct, mult_v(comp.eye_v, n.ratio));
	n.refract = eng_new_ray(comp.under_point, n.direct);
	n.color = eng_color_at(world, n.refract, remaining - 1);
	n.color = scale_fcolor(n.color, comp.obj->material.transparency);
	return (n.color);
}
