#include <ft_matrix.h>
#include <main.h>
#include <ft_engine.h>
#include <libft.h>


int	test_normal_at(void)
{
	t_tuple		soll;
	t_tuple		ist;
	t_tuple		soll2;
	t_tuple		ist2;
	t_sphere	sphere;
	t_sphere	sphere2;
	t_matrix	m2;
	int			flag;

	flag = 1;
	//Test 1
	sphere = eng_new_sphere();
	eng_set_transform((t_obj_ptr)&sphere, mtx_translate(0, 1, 0));
	ist = eng_normal_at((t_obj_ptr)&sphere, new_point(0, 1.70711, -0.70711));
	soll = new_vec(0, 0.70711, -0.70711);

	//TODO: Test 2 failed: Hypothese: mult_mm, mtx_rotation
	sphere2 = eng_new_sphere();
	m2 = mtx_mult_mm(mtx_scale(1, 0.5, 1), mtx_rotation_z(M_PI / 5));
	eng_set_transform((t_obj_ptr)&sphere2, m2);
	ist2 = eng_normal_at((t_obj_ptr)&sphere2, new_point(0, (sqrt(2.0) / 2.0), (-sqrt(2.0) / 2.0)));
	soll2 = new_vec(0, 0.97014, -0.24254);
	if (!eq_t(soll, ist))
	{
		printf("IST: \n");
		print_t(1, ist);
		printf("SOLL: \n");
		print_t(1, soll);
		flag = 0;
	}
	if (!eq_t(soll2, ist2))
	{
		printf("IST2: \n");
		print_t(1, ist2);
		printf("SOLL2: \n");
		print_t(1, soll2);
		flag = 0;
	}
	return (flag);
}
