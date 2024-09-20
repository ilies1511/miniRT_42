#include <ft_engine.h>

t_light	eng_point_light(t_fcolor intensity, t_point position)
{
	t_light	light;

	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = position;
	return (light);
}

t_fcolor	lighting(t_material material, t_light light, t_point hit, t_vec eye, t_vec normal)
{
}

bool	test_lighting(void)
{
	bool		ret = true;
	t_material	material = eng_new_material();
	t_point		position = new_point(0, 0, 0);
	t_vec		eye_v = new_vec(0, 0, -1);
	t_vec		normal_v = new_vec(0, 0, -1);
	t_light		light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	t_fcolor	expected = new_fcolor(1.9, 1.9, 1.9, 1);
	t_fcolor	actual = lighting(material, light, position, eye_v, normal_v);
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
	actual = lighting(material, light, position, eye_v, normal_v);
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
	actual = lighting(material, light, position, eye_v, normal_v);
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
	actual = lighting(material, light, position, eye_v, normal_v);
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
	actual = lighting(material, light, position, eye_v, normal_v);
	if (!eq_fcolor(expected, actual))
	{
		ret = false;
		printf("Test failed: lighting(): test case 5 %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected:\n", expected);
		print_fcolor("actual:\n", actual);
	}
	return (ret);
}
