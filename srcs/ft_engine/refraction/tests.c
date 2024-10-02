#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>


bool	test_prepare_comp_n1_n2(void)
{
	bool			ret = true;
	t_sphere		sph1;
	t_sphere		sph2;
	t_sphere		sph3;
	t_ray			ray;
	t_computation	comp;

	sph1 = eng_new_glass_sphere();
	eng_set_transform((t_obj *)&sph1, mtx_scale(2, 2, 2));
	sph1.base_obj.material.refractive_index = 1.5;
	sph2 = eng_new_glass_sphere();
	eng_set_transform((t_obj *)&sph2, mtx_translate(0, 0, -0.25));
	sph2.base_obj.material.refractive_index = 2.0;
	sph3 = eng_new_glass_sphere();
	eng_set_transform((t_obj *)&sph3, mtx_translate(0, 0, 0.25));
	sph3.base_obj.material.refractive_index = 2.5;
	ray = eng_new_ray(new_point(0, 0, -4), new_vec(0, 0, 1));
	t_intersc		buff[] = {
		{.obj = (t_obj *)&sph1, .t=2},
		{.obj = (t_obj *)&sph2, .t=2.75},
		{.obj = (t_obj *)&sph3, .t=3.25},
		{.obj = (t_obj *)&sph2, .t=4.75},
		{.obj = (t_obj *)&sph3, .t=5.25},
		{.obj = (t_obj *)&sph1, .t=6},
	};
	t_intersc_arr	intersc_arr = eng_new_intersc_arr();
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	dyn_arr_resize((void **)&intersc_arr.arr);
	double	expect_n1[] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
	double	expect_n2[] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};
	ft_memcpy(intersc_arr.arr, buff, sizeof(buff));
	intersc_arr.count = 6;
	for (int i = 0; i < 6; i++)
	{
		comp = eng_prepare_computation(intersc_arr.arr[i], ray, intersc_arr);
		if (!eq_f(comp.n1, expect_n1[i]))
		{
			printf("%s", FT_ANSI_RED_BOLD);
			ret = false;
			printf("Test failed: eng_prepare_computation: n1 is wrong: %s line %d "
					"iteration %d\nexpected: %lf actual: %lf\n", __FILE__,
					__LINE__, i, expect_n1[i], comp.n1);
			printf("%s", FT_ANSI_RESET);
		}
		//else
		//{
		//	printf("%s", FT_ANSI_GREEN_BOLD);
		//	printf("Test passed: n1 is: %lf\n" "iteration %d\n", comp.n1, i);
		//	printf("%s", FT_ANSI_RESET);
		//}
		if (!eq_f(comp.n2, expect_n2[i]))
		{
			printf("%s", FT_ANSI_RED_BOLD);
			ret = false;
			printf("Test failed: eng_prepare_computation: n2 is wrong: %s line %d "
					"iteration %d\nexpected: %lf actual: %lf\n", __FILE__,
					__LINE__, i, expect_n2[i], comp.n2);
			printf("%s", FT_ANSI_RESET);
		}
		//else
		//{
		//	printf("%s", FT_ANSI_GREEN_BOLD);
		//	printf("Test passed: n2 is: %lf\n" "iteration %d\n", comp.n2, i);
		//	printf("%s", FT_ANSI_RESET);
		//}
	}
	eng_free_intersc_arr(&intersc_arr);
	return (ret);
}
