#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>

static inline bool	total_internal_reflect(double sin2_t)
{
	if (sin2_t > 1.0)
		return (true);
	return (false);
}

// returns the reflectance (amount of the light that is reflected)
double	ref_schlick(t_computation comp)
{
	double	cos_eye;
	double	n;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos_eye = dot_prod(norm(comp.eye_v), norm(comp.normal_v));
	if (comp.n1 > comp.n2)
	{
		n = comp.n1 / comp.n2;
		sin2_t = n * n * (1.0 - cos_eye * cos_eye);
		if (total_internal_reflect(sin2_t))
			return (1.0);
		cos_t = sqrt(1.0 - sin2_t);
		cos_eye = cos_t;
	}
	r0 = (comp.n1 - comp.n2) / (comp.n1 + comp.n2);
	r0 *= r0;
	return (r0 + (1.0 - r0) * pow(1.0 - cos_eye, 5));
}

bool	test_schlick_total_internal_reflect(void)
{
	bool			ret = true;
	t_sphere		sph = eng_new_glass_sphere();
	t_ray			ray = eng_new_ray(new_point(0, 0, sqrt(2) / 2), new_vec(0, 1, 0));
	t_intersc		buf[2];
	t_intersc_arr	interscs = {.count = 2, .arr=buf};
	interscs.arr[0].obj = (t_obj_ptr)&sph;
	interscs.arr[1].obj = (t_obj_ptr)&sph;
	interscs.arr[0].t = -sqrt(2)/2;
	interscs.arr[1].t = sqrt(2)/2;
	t_computation comp = eng_prepare_computation(interscs.arr[1], ray, interscs);
	double	actual = ref_schlick(comp);
	double	expect = 1.0;
	if (!eq_f(actual, expect))
	{
		ret = false;
		printf("test failed: ref_schlick: %s line %d\n"
				"expected: %lf\nactual: %lf\n", __FILE__, __LINE__, expect, actual);
	}
	return (ret);
}

bool	test_schlick_perpendicular(void)
{
	bool			ret = true;
	t_sphere		sph = eng_new_glass_sphere();
	t_ray			ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 1, 0));
	t_intersc		buf[2];
	t_intersc_arr	interscs = {.count = 2, .arr=buf};
	interscs.arr[0].obj = (t_obj_ptr)&sph;
	interscs.arr[1].obj = (t_obj_ptr)&sph;
	interscs.arr[0].t = -1;
	interscs.arr[1].t = 1;
	t_computation comp = eng_prepare_computation(interscs.arr[1], ray, interscs);
	double	actual = ref_schlick(comp);
	double	expect = 0.04;
	if (!eq_f(actual, expect))
	{
		ret = false;
		printf("test failed: ref_schlick: %s line %d\n"
				"expected: %lf\nactual: %lf\n", __FILE__, __LINE__, expect, actual);
	}
	return (ret);
}

bool	test_schlick_n2_gt_n1(void)
{
	bool			ret = true;
	t_sphere		sph = eng_new_glass_sphere();
	t_ray			ray = eng_new_ray(new_point(0, 0.99, -2), new_vec(0, 0, 1));
	t_intersc		buf[1];
	t_intersc_arr	interscs = {.count = 1, .arr=buf};
	interscs.arr[0].obj = (t_obj_ptr)&sph;
	interscs.arr[0].t = 1.8589;
	t_computation comp = eng_prepare_computation(interscs.arr[0], ray, interscs);
	double	actual = ref_schlick(comp);
	double	expect = 0.48873;
	if (!eq_f(actual, expect))
	{
		ret = false;
		printf("test failed: ref_schlick: %s line %d\n"
				"expected: %lf\nactual: %lf\n", __FILE__, __LINE__, expect, actual);
	}
	return (ret);
}

bool	test_shade_hit_schlick(void)
{
	bool	ret = true;
	t_world	world = eng_default_world();
	t_ray	ray = eng_new_ray(new_point(0, 0, -3), new_vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	t_plane	floor = eng_new_plane();
	eng_set_transform((t_obj_ptr)&floor, mtx_translate(0, -1, 0));
	floor.base_obj.material.reflective = 0.5;
	floor.base_obj.material.transparency = 0.5;
	floor.base_obj.material.refractive_index = 1.5;
	eng_add_obj_to_world(&world, (t_obj_ptr)&floor);
	t_sphere	ball = eng_new_sphere();
	ball.base_obj.material.fcolor = new_fcolor(1, 0, 0, 1);
	ball.base_obj.material.ambient = 0.5;
	eng_set_transform((t_obj_ptr)&ball, mtx_translate(0, -3.5, -0.5));
	eng_add_obj_to_world(&world, (t_obj_ptr)&ball);
	t_intersc		buf[1];
	t_intersc_arr	interscs = {.count = 1, .arr =buf};
	interscs.arr[0].obj = (t_obj_ptr)&floor;
	interscs.arr[0].t = sqrt(2);
	t_computation	comp = eng_prepare_computation(interscs.arr[0], ray, interscs);
	t_fcolor		actual = eng_shade_hit(world, comp, 5);
	t_fcolor		expect = new_fcolor(0.93391, 0.69643, 0.69243, 1);
	if (!eq_fcolor(actual, expect))
	{
		ret = false;
		printf("test failed: ref_schlick: %s line %d\n", __FILE__, __LINE__);
		print_fcolor("expected: ", expect);
		print_fcolor("actual: ", actual);
	}
	return (ret);
}
