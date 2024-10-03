#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>

/* uses Snell's Law:
 * sin(incoming) / sin(out) = n2 / n1
*/
t_fcolor	refracted_color(t_world world, t_computation comp, size_t remaining)
{
	if (eq_f(comp.obj->material.transparency, 0) || !remaining)
		return (fcolor_black());
	double	cos_vecs = dot_prod(comp.eye_v, comp.normal_v);
	double	ratio = comp.n1 / comp.n2;
	double	sin_sqr = ratio * ratio * (1 - cos_vecs * cos_vecs);
	if (sin_sqr > 1)
		return (fcolor_black());
	double	cos_val = sqrt(1.0 - sin_sqr);
	t_vec	direct = mult_v(comp.normal_v, ratio * cos_vecs - cos_val);
	direct = sub_t(direct, mult_v(comp.eye_v, ratio));
	t_ray	refract = eng_new_ray(comp.under_point, direct);
	t_fcolor	color = eng_color_at(world, refract, remaining - 1);
	color = scale_fcolor(color, comp.obj->material.transparency);
	return (color);
}
