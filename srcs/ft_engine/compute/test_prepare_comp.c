#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>
#include <ft_reflection.h>

bool	test_prepare_computation(void)
{
	t_intersc_arr	interscs = eng_new_intersc_arr();
	dyn_arr_resize((void **)&interscs.arr);
	interscs.count = 1;
	bool		ret = true;
	t_ray		ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_sphere	sph = eng_new_sphere();
	t_intersc	intersc = {.t=4, .obj = (t_obj_ptr)&sph};
	t_computation	expect;
	ft_bzero(&expect, sizeof expect);
	expect.t = intersc.t;
	expect.obj = intersc.obj;
	expect.point = new_point(0, 0, -1);
	expect.eye_v = new_vec(0, 0, -1);
	expect.normal_v = new_vec(0, 0, -1);
	interscs.count = 1;
	interscs.arr[0] = intersc;
	t_computation	actual = eng_prepare_computation(intersc, ray, interscs);
	if (!eq_f(actual.t, expect.t))
	{
		ft_fprintf(2, "Failed at %s:%d: expected t %f, got %f\n", __FILE__, __LINE__, expect.t, actual.t);
		ret = false;
	}
	if (actual.obj != expect.obj)
	{
		ft_fprintf(2, "Failed at %s:%d: expected object pointer to match\n", __FILE__, __LINE__);
		ret = false;
	}
	if (!eq_t(actual.point, expect.point))
	{
		ft_fprintf(2, "Failed at %s:%d: expected point ", __FILE__, __LINE__);
		print_t(2, expect.point);
		ft_fprintf(2, ", got ");
		print_t(2, actual.point);
		ft_fprintf(2, "\n");
		ret = false;
	}
	if (!eq_t(actual.eye_v, expect.eye_v))
	{
		ft_fprintf(2, "Failed at %s:%d: expected eye vector ", __FILE__, __LINE__);
		print_t(2, expect.eye_v);
		ft_fprintf(2, ", got ");
		print_t(2, actual.eye_v);
		ft_fprintf(2, "\n");
		ret = false;
	}
	if (!eq_t(actual.normal_v, expect.normal_v))
	{
		ft_fprintf(2, "Failed at %s:%d: expected normal vector ", __FILE__, __LINE__);
		print_t(2, expect.normal_v);
		ft_fprintf(2, ", got ");
		print_t(2, actual.normal_v);
		ft_fprintf(2, "\n");
		ret = false;
	}

	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersc.t = 4;
	intersc.obj = (t_obj_ptr)&sph;
	interscs.arr[0] = intersc;
	actual = eng_prepare_computation(intersc, ray, interscs);
	if (actual.inside != false)
	{
		ft_fprintf(2, "Test failed at %s:%d: expected 'inside' to be false, got %s\n", __FILE__, __LINE__, actual.inside ? "true" : "false");
		ret = false;
	}

	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersc.t = 1;
	intersc.obj = (t_obj_ptr)&sph;
	interscs.arr[0] = intersc;
	actual = eng_prepare_computation(intersc, ray, interscs);
	if (!eq_t(actual.point, new_point(0, 0, 1)))
	{
		ft_fprintf(2, "Test failed at %s:%d: expected point to be (0, 0, 1), got ", __FILE__, __LINE__);
		print_t(2, actual.point);
		ft_fprintf(2, "\n");
		ret = false;
	}
	if (!eq_t(actual.eye_v, new_vec(0, 0, -1)))
	{
		ft_fprintf(2, "Test failed at %s:%d: expected eye vector to be (0, 0, -1), got ", __FILE__, __LINE__);
		print_t(2, actual.eye_v);
		ft_fprintf(2,"\n");
		ret = false;
	}
	if (!eq_t(actual.normal_v, new_vec(0, 0, -1)))
	{
		ft_fprintf(2, "Test failed at %s:%d: expected normal vector to be inverted (0, 0, -1), got ", __FILE__, __LINE__);
		print_t(2, actual.normal_v);
		ft_fprintf(2, "\n");
		ret = false;
	}
	if (actual.inside != true)
	{
		ft_fprintf(2,"Test failed at %s:%d: expected 'inside' to be true, got %s\n", __FILE__, __LINE__, actual.inside ? "true" : "false");
		ret = false;
	}

	t_plane plane = eng_new_plane();
	ray = eng_new_ray(new_point(0, 1, -1), new_vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	intersc.t = sqrt(2);
	intersc.obj = (t_obj_ptr)&plane;
	interscs.arr[0] = intersc;
	actual = eng_prepare_computation(intersc, ray, interscs);
	if (!eq_t(actual.reflection, new_vec(0, sqrt(2) / 2, sqrt(2) / 2)))
	{
		ft_fprintf(2,"Test failed at %s:%d: prepare compt reflection is wrong\n", __FILE__, __LINE__);
		ret = false;
	}
	eng_free_intersc_arr(&interscs);
	return (ret);
}

