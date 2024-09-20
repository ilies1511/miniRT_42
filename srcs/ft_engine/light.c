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
	return (light);
}
