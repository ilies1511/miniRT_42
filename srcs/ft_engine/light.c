#include <ft_engine.h>
#include <main.h>
#include <ft_patterns.h>

t_fcolor	eng_mult_color_f(t_fcolor color1, double scale)
{
	t_fcolor	result;

	result.r = color1.r * scale;
	result.g = color1.g * scale;
	result.b = color1.b * scale;
	result.a = color1.a * scale;
	return (result);
}

t_fcolor	eng_add_color_color(t_fcolor color1, t_fcolor color2)
{
	t_fcolor	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	result.a = color1.a + color2.a;
	return (result);
}

t_fcolor	eng_mult_color_color(t_fcolor color1, t_fcolor color2)
{
	t_fcolor	result;

	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	result.a = color1.a * color2.a;
	return (result);
}

static void	init_lighting_norm_strukt(t_lighting_norm	*light_norm)
{
	light_norm->ambient_c = new_fcolor(0, 0, 0, 0);
	light_norm->diffuse_c = new_fcolor(0, 0, 0, 0);
	light_norm->effective_color = new_fcolor(0, 0, 0, 0);
	light_norm->factor = 0;
	light_norm->light_direction = sub_t(new_vec(0, 0, 0), new_vec(0, 0, 0));
	light_norm->light_dot_normal = 0;
	light_norm->lightv = new_vec(0, 0, 0);
}

static void	in_light_case(t_lighting_norm *n, t_light light, t_computation comp)
{
	n->diffuse_c = scale_fcolor(scale_fcolor(n->effective_color,
				(comp.obj->material.diffuse)), n->light_dot_normal);
	n->reflectv = ref_reflect(negate_v(n->lightv), comp.normal_v);
	n->reflect_dot_eye = dot_prod(n->reflectv, comp.eye_v);
	if (n->reflect_dot_eye <= 0)
		n->specular_c = new_fcolor(0, 0, 0, 1);
	else
	{
		n->factor = pow(n->reflect_dot_eye, (comp.obj->material.shininess));
		n->specular_c = scale_fcolor(light.intensity,
				comp.obj->material.specular * n->factor);
	}
}

//Improved Light Function: bool in_shadow,
//which will make sure the pixel in question will not be fully lighten up
t_fcolor	eng_lighting(t_computation comp, t_light light, bool in_shadow)
{
	t_lighting_norm	n;

	init_lighting_norm_strukt(&n);
	if (!(comp.obj->material.pattern))
		n.effective_color = mult_fcolor((comp.obj->material.fcolor),
				light.intensity);
	else
		n.effective_color = pat_color_at(*(comp.obj),
				*(comp.obj->material.pattern), comp.over_point);
	n.light_direction = sub_t(light.origin, comp.over_point);
	n.lightv = norm(new_vec(n.light_direction.x, n.light_direction.y,
				n.light_direction.z));
	n.ambient_c = scale_fcolor(n.effective_color, comp.obj->material.ambient);
	n.light_dot_normal = dot_prod(n.lightv, comp.normal_v);
	if (n.light_dot_normal < 0)
	{
		//Light is on the other side of the surface--> BLACK
		n.diffuse_c = new_fcolor(0, 0, 0, 1);
		n.specular_c = new_fcolor(0, 0, 0, 1);
	}
	else
		in_light_case(&n, light, comp);
	if (in_shadow)
		return (n.ambient_c);
	return (add_fcolor(add_fcolor(n.ambient_c, n.diffuse_c), n.specular_c));
}

t_light	eng_point_light(t_fcolor intensity, t_point position)
{
	t_light	light;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	light.base_obj.type = OBJ_LIGHT;
	return (light);
}
