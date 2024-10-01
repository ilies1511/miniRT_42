#include <ft_patterns.h>
#include <main.h>

bool	test_stripe_pattern(void)
{
	bool	ret = true;
	t_pattern	*pat;
	t_fcolor	actual_color;

	pat = pat_stripe_pattern(fcolor_white(), fcolor_black());
	if (!eq_fcolor(fcolor_white(), pat->colors[0])
		|| !eq_fcolor(fcolor_white(), pat->colors[0]))
	{
		printf("Test failed: pat_stripe_pattern: wrong color: %s line %d\n",
				__FILE__, __LINE__);
		ret = false;
	}
	if (pat->color_count != 2)
	{
		printf("Test failed: pat_stripe_pattern: wrong color count: %s line %d\n",
				__FILE__, __LINE__);
		ret = false;
	}

	actual_color = pat_stripe_at(*pat, new_point(0, 0, 0));
	if (!eq_fcolor(actual_color, fcolor_white()))
	{
		ret = false;
		printf("Test failed: pat_stripe_at: wrong color returned: %s line %d\n",
			__FILE__, __LINE__);
		print_fcolor("expected: ", fcolor_white());
		print_fcolor("actual: ", actual_color);
	}

	for (int z = 0; z <= 2; z++)
	{
		actual_color = pat_stripe_at(*pat, new_point(0, 0, z));
		if (!eq_fcolor(actual_color, fcolor_white()))
		{
			ret = false;
			printf("Test failed: pat_stripe_at (constant in z) at z=%d: wrong color returned: %s line %d\n", z, __FILE__, __LINE__);
			print_fcolor("expected: ", fcolor_white());
			print_fcolor("actual: ", actual_color);
		}
	}

	double xs[] = {0, 0.9, 1, -0.1, -1, -1.1};
	t_fcolor expected_colors[] = {fcolor_white(), fcolor_white(), fcolor_black(), fcolor_black(), fcolor_black(), fcolor_white()};
	for (int i = 0; i < 6; i++)
	{
		actual_color = pat_stripe_at(*pat, new_point(xs[i], 0, 0));
		if (!eq_fcolor(actual_color, expected_colors[i]))
		{
			ret = false;
			printf("Test failed: pat_stripe_at (alternates in x) at x=%.1f: wrong color returned: %s line %d\n", xs[i], __FILE__, __LINE__);
			print_fcolor("expected: ", expected_colors[i]);
			print_fcolor("actual: ", actual_color);
		}
	}
	return (ret);
}

bool	test_stripe_lighting(void)
{
	bool	ret = true;
	t_material	material;
	t_vec		eye_v;
	t_vec		normal;
	t_light		light;
	t_fcolor	expect;
	t_fcolor	actual;

	material = eng_new_material();
	material.pattern = pat_stripe_pattern(fcolor_white(), fcolor_black());
	material.ambient = 1;
	material.diffuse = 0;
	material.specular = 0;
	light = eng_point_light(fcolor_white(), new_point(0, 0, -10));
	eye_v = new_vec(0, 0, -1);
	normal = new_vec(0, 0, -1);
	expect = fcolor_white();
	actual = eng_lighting_impr(material, light, new_point(0.9, 0, 0), eye_v, normal, false);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("Test fail: eng_lighting with pattern stripe: %s line %d\n",
			__FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	expect = fcolor_black();
	actual = eng_lighting_impr(material, light, new_point(1.1, 0, 0), eye_v, normal, false);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("Test fail: eng_lighting with pattern stripe: %s line %d\n",
			__FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	return (ret);
}

bool	test_stripe_obj(void)
{
	bool		ret = true;
	t_sphere	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_scale(2, 2, 2));
	t_pattern	*pat = pat_stripe_pattern(fcolor_white(), fcolor_black());
	sph.base_obj.material.pattern = pat;
	t_fcolor	actual = pat_color_at(sph.base_obj, *pat, new_point(1.5, 0, 0));
	t_fcolor	expect = fcolor_white();
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: pat_stripe_at_object: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}

	sph = eng_new_sphere();
	pat = pat_stripe_pattern(fcolor_white(), fcolor_black());
	eng_set_transform((t_obj *)pat, mtx_scale(2, 2, 2));
	sph.base_obj.material.pattern = pat;
	actual = pat_color_at(sph.base_obj, *pat, new_point(1.5, 0, 0));
	expect = fcolor_white();
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: pat_set_transform: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_scale(2, 2, 2));
	pat = pat_stripe_pattern(fcolor_white(), fcolor_black());
	eng_set_transform((t_obj *)pat, mtx_translate(0.5, 0, 0));
	sph.base_obj.material.pattern = pat;
	actual = pat_color_at(sph.base_obj, *pat, new_point(2.5, 0, 0));
	expect = fcolor_white();
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: pat_set_transform: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	return (ret);
}
