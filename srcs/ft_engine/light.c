#include <ft_engine.h>
#include <main.h>

t_fcolor	eng_mult_color_f(t_fcolor color1, float scale)
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
	bool		ret = true;
	bool		in_shadow = true;
	t_vec		eye_v = new_vec(0, 0, -1);
	t_vec		normal_v = new_vec(0, 0, -1);
	t_light		light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));

	t_material	material = eng_new_material();
	t_point		position = new_point(0, 0, 0);
	t_fcolor	expected = new_fcolor(1.9, 1.9, 1.9, 1);
	t_fcolor	actual = eng_lighting(material, light, position, eye_v, normal_v);

	eye_v = new_vec(0, 0, -1);
	normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, 10));
	expected = new_fcolor(0.1, 0.1, 0.1, 1);
	actual = eng_lighting_impr(material, light, position, eye_v, normal_v, in_shadow);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 5 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	return (ret);
}

//Improved Light Function: bool in_shadow, which will make sure the pixel in question will not be fully lighten up
t_fcolor	eng_lighting_impr(t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv, bool in_shadow)
{
	t_fcolor	result;
	t_fcolor	effective_color;
	t_fcolor	ambient_c;
	t_vec		lightv;
	t_vec		reflectv;
	t_tuple		light_direction;
	float		light_dot_normal;
	float		reflect_dot_eye;
	double		factor;
	t_fcolor	diffuse_c;
	t_fcolor	specular_c;

	effective_color = eng_mult_color_color(material.fcolor, light.intensity);
	light_direction = sub_t(light.origin, point);
	lightv = norm(new_vec(light_direction.x, light_direction.y, light_direction.z));
	ambient_c = eng_mult_color_f(effective_color, material.ambient);
	light_dot_normal = dot_prod(lightv, normalv);
	if (light_dot_normal < 0)
	{
		//Light is on the other side of the surface--> BLACK
		diffuse_c = new_fcolor(0, 0, 0, 1);
		specular_c = new_fcolor(0, 0, 0, 1);
	}
	else
	{
		diffuse_c = eng_mult_color_f(eng_mult_color_f(effective_color, material.diffuse), light_dot_normal); // ?
		reflectv = eng_reflect(negate_v(lightv), normalv);
		reflect_dot_eye = dot_prod(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular_c = new_fcolor(0, 0, 0, 1);
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			specular_c = eng_mult_color_f(light.intensity, (material.specular * factor));
		}
	}
	// result = ambient + diffuse_c + specular_c
	if (in_shadow)
	{
		ambient_c.a = 1; //TODO: Wie wichtig ist hier der a value ?
		return (ambient_c);
	}
	result = add_fcolor(add_fcolor(ambient_c, diffuse_c), specular_c);
	return (result);
}
t_fcolor	eng_lighting(t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv)
{
	t_fcolor	result;
	t_fcolor	effective_color;
	t_fcolor	ambient_c;
	t_vec		lightv;
	t_vec		reflectv;
	t_tuple		light_direction;
	float		light_dot_normal;
	float		reflect_dot_eye;
	double		factor;
	t_fcolor	diffuse_c;
	t_fcolor	specular_c;

	effective_color = eng_mult_color_color(material.fcolor, light.intensity);
	light_direction = sub_t(light.origin, point);
	lightv = norm(new_vec(light_direction.x, light_direction.y, light_direction.z));
	ambient_c = eng_mult_color_f(effective_color, material.ambient);
	light_dot_normal = dot_prod(lightv, normalv);
	if (light_dot_normal < 0)
	{
		//Light is on the other side of the surface--> BLACK
		diffuse_c = new_fcolor(0, 0, 0, 1);
		specular_c = new_fcolor(0, 0, 0, 1);
	}
	else
	{
		diffuse_c = eng_mult_color_f(eng_mult_color_f(effective_color, material.diffuse), light_dot_normal); // ?
		reflectv = eng_reflect(negate_v(lightv), normalv);
		reflect_dot_eye = dot_prod(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular_c = new_fcolor(0, 0, 0, 1);
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			specular_c = eng_mult_color_f(light.intensity, (material.specular * factor));
		}
	}
	// result = ambient + diffuse_c + specular_c
	result = add_fcolor(add_fcolor(ambient_c, diffuse_c), specular_c);
	return (result);
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



bool	test_eng_lighting(void)
{
	bool		ret = true;
	t_material	material = eng_new_material();
	t_point		position = new_point(0, 0, 0);
	t_vec		eye_v = new_vec(0, 0, -1);
	t_vec		normal_v = new_vec(0, 0, -1);
	t_light		light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	t_fcolor	expected = new_fcolor(1.9, 1.9, 1.9, 1);
	t_fcolor	actual = eng_lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 1 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}

	eye_v = new_vec(0, sqrt(2) / 2, -sqrt(2) / 2);
	normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	expected = new_fcolor(1, 1, 1, 1);
	actual = eng_lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 2 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}

	eye_v = new_vec(0, 0, -1);
	normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, -10));
	expected = new_fcolor(0.7364, 0.7364, 0.7364, 1);
	actual = eng_lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 3 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}

	eye_v = new_vec(0, -sqrt(2) / 2, -sqrt(2) / 2);
	normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, -10));
	expected = new_fcolor(1.6364, 1.6364, 1.6364, 1);
	actual = eng_lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 4 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}

	eye_v = new_vec(0, 0, -1);
	normal_v = new_vec(0, 0, -1);
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 10, 10));
	expected = new_fcolor(0.1, 0.1, 0.1, 1);
	actual = eng_lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 5 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	return (ret);
}
