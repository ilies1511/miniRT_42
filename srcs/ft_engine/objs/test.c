#include <main.h>
#include <ft_engine.h>
#include <ft_matrix.h>

bool	test_eng_trasform(void)
{
	bool		ret = true;
	t_ray		ray_base;
	t_ray		expected;
	t_ray		actual;

	ray_base = eng_new_ray(new_point(1, 2, 3), new_vec(0, 1, 0));
	ray_base.base_obj.transform = mtx_translate(3, 4, 5);
	expected = eng_new_ray(new_point(4, 6, 8), new_vec(0, 1, 0));
	eng_transform((t_obj *)&ray_base, (t_obj *)&actual);
	if (!eng_eq_ray(actual, expected))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_transform_ray: %s line %d\n", __FILE__, __LINE__);
	}

	ray_base = eng_new_ray(new_point(1, 2, 3), new_vec(0, 1, 0));
	ray_base.base_obj.transform = mtx_scale(2, 3, 4);
	expected = eng_new_ray(new_point(2, 6, 12), new_vec(0, 3, 0));
	eng_transform((t_obj *)&ray_base, (t_obj *)&actual);
	if (!eng_eq_ray(actual, expected))
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_transform: %s line %d\n", __FILE__, __LINE__);
	}
	return (ret);
}

bool	test_transformation_matrices(void)
{
	bool			ret = true;
	t_sphere		sph;
	t_matrix		transform;
	t_ray			ray;
	t_intersc_arr	interscs = eng_new_intersc_arr();

	sph = eng_new_sphere();
	if (!mtx_eq(sph.base_obj.transform, mtx_new_ident(MAT4X4))
		|| !mtx_eq(sph.base_obj.inverse, mtx_new_ident(MAT4X4))
	)
	{
		ret = false;
		fprintf(stderr, "Test failed: eng_new_sphere: \
				new sphere does not have idennt matrix: %s line %d\n",
				__FILE__, __LINE__);
	}

	transform = mtx_translate(2, 3, 4);
	eng_set_transform((t_obj *) &sph, transform);
	if (!mtx_eq(sph.base_obj.transform, transform)
		|| !mtx_eq(sph.base_obj.inverse, mtx_inverse(transform))
	)
	{
		ret = false;
		fprintf(stderr, "Test failed: %s line %d\n", __FILE__, __LINE__);
	}

	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_scale(2, 2, 2));
	eng_intersc_ray(&interscs, &ray, (t_obj *)&sph);
	eng_sort_intersc(&interscs);
	if (interscs.count != 2)
	{
		ret = false;
		fprintf(stderr, "Test failed: %s line %d\n", __FILE__, __LINE__);
	}
	if (interscs.count && !eq_f(interscs.arr[0].t, 3))
	{
		ret = false;
		fprintf(stderr, "Test failed: %s line %d\n", __FILE__, __LINE__);
		printf("expected: %f, actual: %f\n", 3.0, interscs.arr[0].t);
	}
	if (interscs.count > 1 && !eq_f(interscs.arr[1].t, 7))
	{
		ret = false;
		fprintf(stderr, "Test failed: %s line %d\n", __FILE__, __LINE__);
		printf("expected: %f, actual: %f\n", 7.0, interscs.arr[1].t);
	}
	eng_free_intersc_arr(&interscs);

	ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	sph = eng_new_sphere();
	eng_set_transform((void *)&sph, mtx_translate(5, 0, 0));
	eng_intersc_ray(&interscs, &ray, (t_obj *) &sph);
	if (interscs.count != 0)
	{
		ret = false;
		fprintf(stderr, "Test failed: %s line %d\n", __FILE__, __LINE__);
	}
	eng_free_intersc_arr(&interscs);

	return (ret);
}
