#include <ft_engine.h>
#include <main.h>
#include <ft_patterns.h>

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
