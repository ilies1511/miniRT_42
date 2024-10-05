#include <ft_engine.h>
#include <main.h>
#include <ft_patterns.h>

static void	init_lighting_norm_strukt(t_lighting_norm *light_norm)
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

//static void	no_light_case(t_lighting_norm *n)
//{
//	n->diffuse_c = new_fcolor(0, 0, 0, 1);
//	n->specular_c = new_fcolor(0, 0, 0, 1);
//}

// good lighting but that dosnt do what subject does
//Improved Light Function: bool in_shadow,
//which will make sure the pixel in question will not be fully lighten up
t_fcolor	eng_lighting(t_computation comp, t_light light, bool in_shadow)
{
	t_lighting_norm	n;

	init_lighting_norm_strukt(&n);
	t_fcolor check = mult_fcolor(comp.color_at, light.intensity);
	n.effective_color = mult_fcolor(comp.color_at, light.intensity);
	n.light_direction = sub_t(light.origin, comp.over_point);
	n.lightv = norm(new_vec(n.light_direction.x, n.light_direction.y, \
		n.light_direction.z));
	n.lightv = norm(new_vec(n.light_direction.x, n.light_direction.y,
				n.light_direction.z));
	n.ambient_c = scale_fcolor(n.effective_color, comp.obj->material.ambient);
	if (in_shadow)
		return (n.ambient_c);
	n.light_dot_normal = dot_prod(n.lightv, comp.normal_v);
	if (n.light_dot_normal < 0)
		return (n.ambient_c);
	in_light_case(&n, light, comp);
	return (add_fcolor(add_fcolor(n.ambient_c, n.diffuse_c), n.specular_c));
}

t_fcolor	eng_lighting42(t_computation comp, t_light light)
{
	t_lighting_norm	n;

	init_lighting_norm_strukt(&n);
	n.effective_color = mult_fcolor(comp.color_at, light.intensity);
	n.light_direction = sub_t(light.origin, comp.over_point);
	n.lightv = norm(new_vec(n.light_direction.x, n.light_direction.y, \
		n.light_direction.z));
	n.lightv = norm(new_vec(n.light_direction.x, n.light_direction.y,
				n.light_direction.z));
	n.ambient_c = fcolor_black();
	n.light_dot_normal = dot_prod(n.lightv, comp.normal_v);
	if (n.light_dot_normal < 0)
		return (n.ambient_c);
	in_light_case(&n, light, comp);
	return (add_fcolor(add_fcolor(n.ambient_c, n.diffuse_c), n.specular_c));
}

t_light	eng_point_light(t_fcolor intensity, t_point position)
{
	t_light	light;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	light.base_obj.type = OBJ_LIGHT;
	light.radius = 1;
	light.type = POINT_LIGHT;
	return (light);
}

t_light			eng_spot_light(t_fcolor intensity, t_point position,
		t_point look_at, double fov_360)
{
	t_light	light;
	double	rad_angle;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	light.base_obj.type = OBJ_LIGHT;
	light.radius = 1;
	light.type = SPOT_LIGHT;
	light.direct = sub_t(look_at, position);
	light.direct = norm(light.direct);
	rad_angle = fov_360 / 180 * M_PI / 2;
	light.cosine_range = cos(rad_angle);
	return (light);
}
