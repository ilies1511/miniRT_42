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

bool	test_light_with_surface_shadow()
{
	t_computation	comp;
	bool		ret = true;
	bool		in_shadow = true;
	t_light		light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));

	comp.obj = ft_malloc(sizeof(t_obj));
	*(comp.obj) = eng_new_obj();
	comp.eye_v = new_vec(0, 0, -1);
	comp.normal_v = new_vec(0, 0, -1);
	comp.obj->material = eng_new_material();
	comp.over_point = new_point(0, 0, 0);
	t_fcolor	expected = new_fcolor(1.9, 1.9, 1.9, 1);
	t_fcolor	actual = eng_lighting(comp, light, false);

	comp.eye_v = new_vec(0, 0, -1);
	comp.normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, 10));
	expected = new_fcolor(0.1, 0.1, 0.1, 1);
	actual = eng_lighting(comp, light, in_shadow);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 5 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	return (ret);
}

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
	n->diffuse_c = scale_fcolor(scale_fcolor(n->effective_color, (comp.obj->material.diffuse)), n->light_dot_normal); // ?
	n->reflectv = ref_reflect(negate_v(n->lightv), comp.normal_v);
	n->reflect_dot_eye = dot_prod(n->reflectv, comp.eye_v);
	if (n->reflect_dot_eye <= 0)
		n->specular_c = new_fcolor(0, 0, 0, 1);
	else
	{
		n->factor = pow(n->reflect_dot_eye, (comp.obj->material.shininess));
		n->specular_c = scale_fcolor(light.intensity, ((comp.obj->material.specular) * n->factor));
	}
}

t_fcolor	eng_lighting(t_computation comp, t_light light, bool in_shadow)
{
	t_lighting_norm	n;

	init_lighting_norm_strukt(&n);
	if (!(comp.obj->material.pattern))
		n.effective_color = mult_fcolor((comp.obj->material.fcolor), \
			light.intensity);
	else
		n.effective_color = pat_color_at(*(comp.obj), \
			*(comp.obj->material.pattern), (comp.over_point));
	n.light_direction = sub_t(light.origin, comp.over_point);
	n.lightv = norm(new_vec((n.light_direction.x), (n.light_direction.y), \
		(n.light_direction.z)));
	n.ambient_c = scale_fcolor(n.effective_color, comp.obj->material.ambient);
	n.light_dot_normal = dot_prod(n.lightv, comp.normal_v);
	if (n.light_dot_normal < 0)
	{
		n.diffuse_c = new_fcolor(0, 0, 0, 1);
		n.specular_c = new_fcolor(0, 0, 0, 1);
	}
	else
		in_light_case(&n, light, comp);
	if (in_shadow)
		return (n.ambient_c);
	return (add_fcolor(add_fcolor(n.ambient_c, n.diffuse_c), n.specular_c));
}
// //Improved Light Function: bool in_shadow, which will make sure the pixel in question will not be fully lighten up
// t_fcolor	eng_lighting(t_obj obj, t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv, bool in_shadow)
// {
// 	t_fcolor	result;
// 	t_fcolor	effective_color;
// 	t_fcolor	ambient_c;
// 	t_vec		lightv;
// 	t_vec		reflectv;
// 	t_tuple		light_direction;
// 	double		light_dot_normal;
// 	double		reflect_dot_eye;
// 	double		factor;
// 	t_fcolor	diffuse_c;
// 	t_fcolor	specular_c;

// 	if (!material.pattern)
// 		effective_color = mult_fcolor(material.fcolor, light.intensity);
// 	else
// 		effective_color = pat_color_at(obj, *material.pattern, point);
// 	light_direction = sub_t(light.origin, point);
// 	lightv = norm(new_vec(light_direction.x, light_direction.y, light_direction.z));
// 	ambient_c = scale_fcolor(effective_color, material.ambient);
// 	light_dot_normal = dot_prod(lightv, normalv);
// 	if (light_dot_normal < 0)
// 	{
// 		//Light is on the other side of the surface--> BLACK
// 		diffuse_c = new_fcolor(0, 0, 0, 1);
// 		specular_c = new_fcolor(0, 0, 0, 1);
// 	}
// 	else
// 	{
// 		diffuse_c = scale_fcolor(scale_fcolor(effective_color, material.diffuse), light_dot_normal); // ?
// 		reflectv = ref_reflect(negate_v(lightv), normalv);
// 		reflect_dot_eye = dot_prod(reflectv, eyev);
// 		if (reflect_dot_eye <= 0)
// 			specular_c = new_fcolor(0, 0, 0, 1);
// 		else
// 		{
// 			factor = pow(reflect_dot_eye, material.shininess);
// 			specular_c = scale_fcolor(light.intensity, (material.specular * factor));
// 		}
// 	}
// 	// result = ambient + diffuse_c + specular_c
// 	if (in_shadow)
// 		return (ambient_c);
// 	result = add_fcolor(add_fcolor(ambient_c, diffuse_c), specular_c);
// 	return (result);
// }

t_light	eng_point_light(t_fcolor intensity, t_point position)
{
	t_light	light;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	light.base_obj.type = OBJ_LIGHT;
	return (light);
}

bool	test_eng_lighting(void)
{
	bool			ret = true;
	t_computation	comp;
	t_light			light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));

	//eng_prepare_computation();
	comp.obj = ft_malloc(sizeof(t_obj));
	*(comp.obj) = eng_new_obj();
	comp.obj->material = eng_new_material();
	comp.over_point = new_point(0, 0, 0);
	comp.eye_v = new_vec(0, 0, -1);
	comp.normal_v = new_vec(0, 0, -1);
	t_fcolor	expected = new_fcolor(1.9, 1.9, 1.9, 1);
	t_fcolor	actual = eng_lighting(comp, light, false);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 1 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	*(comp.obj) = eng_new_obj();
	comp.eye_v = new_vec(0, sqrt(2) / 2, -sqrt(2) / 2);
	comp.normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	expected = new_fcolor(1, 1, 1, 1);
	actual = eng_lighting(comp, light, false);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 2 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}

	*(comp.obj) = eng_new_obj();
	comp.eye_v = new_vec(0, 0, -1);
	comp.normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, -10));
	expected = new_fcolor(0.7364, 0.7364, 0.7364, 1);
	actual = eng_lighting(comp, light, false);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 3 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	*(comp.obj) = eng_new_obj();
	comp.eye_v = new_vec(0, -sqrt(2) / 2, -sqrt(2) / 2);
	comp.normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, -10));
	expected = new_fcolor(1.6364, 1.6364, 1.6364, 1);
	actual = eng_lighting(comp, light, false);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 4 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	*(comp.obj) = eng_new_obj();
	comp.eye_v = new_vec(0, 0, -1);
	comp.normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, 10));
	expected = new_fcolor(0.1, 0.1, 0.1, 1);
	actual = eng_lighting(comp, light, false);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 5 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	return (ret);
}
