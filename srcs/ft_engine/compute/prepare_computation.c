#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>

t_point	mult_p_scalar(t_point point, float scale)
{
	t_point	new;

	new.x = point.x * scale;
	new.y = point.y * scale;
	new.z = point.z * scale;
	return (new);
}

t_computation	eng_prepare_computation(t_intersc intersc, t_ray ray)
{
	t_computation	comp;
	ft_bzero(&comp, sizeof comp);
	comp.t = intersc.t;
	comp.obj = intersc.obj;
	comp.point = eng_ray_pos(ray, comp.t);
	// comp.over_point = eng_ray_pos(ray, comp.t);
	comp.eye_v = negate_v(ray.direct);
	comp.normal_v = eng_normal_at(comp.obj, comp.point);
	if (dot_prod(comp.normal_v, comp.eye_v) < 0)
	{
		comp.inside = true;
		comp.normal_v = negate_v(comp.normal_v);
	}
	else
		comp.inside = false;
	// comp.over_point = mult_p_scalar(add_t(comp.point, comp.normal_v), EPSILON);
	comp.over_point = add_t(comp.point, mult_v(comp.normal_v, EPSILON)); //TODO: not sure if correct
	return (comp);
}

bool	test_prepare_computation(void)
{
	bool		ret = true;
	t_ray		ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_sphere	sph = eng_new_sphere();
	t_intersc	intersc = {.t=4, .obj = (t_obj *)&sph};
	t_computation	expect;
	ft_bzero(&expect, sizeof expect);
	expect.t = intersc.t;
	expect.obj = intersc.obj;
	expect.point = new_point(0, 0, -1);
	expect.eye_v = new_vec(0, 0, -1);
	expect.normal_v = new_vec(0, 0, -1);
	t_computation	actual = eng_prepare_computation(intersc, ray);
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
	intersc.obj = (t_obj *)&sph;
	actual = eng_prepare_computation(intersc, ray);
	if (actual.inside != false)
	{
		ft_fprintf(2, "Test failed at %s:%d: expected 'inside' to be false, got %s\n", __FILE__, __LINE__, actual.inside ? "true" : "false");
		ret = false;
	}

	ray = eng_new_ray(new_point(0, 0, 0), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	intersc.t = 1;
	intersc.obj = (t_obj *)&sph;
	actual = eng_prepare_computation(intersc, ray);
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
	return (ret);
}

