#include <ft_engine.h>
#include <main.h>

bool	test_transformation_view_mixed(void)
{
	t_point		from;
	t_point		to;
	t_vec		up;
	t_matrix	ist;
	t_matrix	soll;
	bool		flag;

	soll = mtx_new_ident(MAT4X4);
	soll.m[0][0] = -0.50709;
	soll.m[0][1] = 0.50709;
	soll.m[0][2] = 0.67612;
	soll.m[0][3] = -2.36643;
	soll.m[1][0] = 0.76772;
	soll.m[1][1] = 0.60609;
	soll.m[1][2] = 0.12122;
	soll.m[1][3] = -2.82843;
	soll.m[2][0] = -0.35857;
	soll.m[2][1] = 0.59761;
	soll.m[2][2] = -0.71714;
	soll.m[2][3] = 0;
	soll.m[3][0] = 0;
	soll.m[3][1] = 0;
	soll.m[3][2] = 0;
	soll.m[3][3] = 1;
	from = new_point(1, 3, 2);
	to = new_point(4, -2, 8);
	up = new_vec(1, 1, 0);
	ist = sc_transforme_view(from, to, up);
	flag = mtx_eq(ist, soll);
	if (!flag)
	{
		printf("IST: \n");
		mtx_print_matrix(&ist, MAT4X4);
		printf("\n");
		printf("SOLL: \n");
		mtx_print_matrix(&soll, MAT4X4);
	}
	return(flag);
}

bool	test_transformation_view_world(void)
{
	t_point		from;
	t_point		to;
	t_vec		up;
	t_matrix	ist;
	t_matrix	soll;
	bool		flag;

	soll = mtx_translate(0, 0, -8);
	from = new_point(0, 0, 8);
	to = new_point(0, 0, 0);
	up = new_vec(0, 1, 0);
	ist = sc_transforme_view(from, to, up);
	flag = mtx_eq(ist, soll);
	if (!flag)
	{
		printf("IST: \n");
		mtx_print_matrix(&ist, MAT4X4);
		printf("\n");
		printf("SOLL: \n");
		mtx_print_matrix(&soll, MAT4X4);
	}
	return(flag);
}

bool	test_transformation_view_z(void)
{
	t_point		from;
	t_point		to;
	t_vec		up;
	t_matrix	ist;
	t_matrix	soll;

	soll = mtx_scale(-1, 1, -1);
	from = new_point(0, 0, 0);
	to = new_point(0, 0, 1);
	up = new_vec(0, 1, 0);
	ist = sc_transforme_view(from, to, up);
	if (!mtx_eq(ist, soll))
	{
		printf("IST: \n");
		mtx_print_matrix(&ist, MAT4X4);
		printf("\n");
		printf("SOLL: \n");
		mtx_print_matrix(&soll, MAT4X4);
	}
	return(mtx_eq(ist, soll));
}

bool	test_transformation_view_default(void)
{
	t_point		from;
	t_point		to;
	t_vec		up;
	t_matrix	ist;
	t_matrix	soll;

	soll = mtx_new_ident(MAT4X4);
	from = new_point(0, 0, 0);
	to = new_point(0, 0, -1);
	up = new_vec(0, 1, 0);
	ist = sc_transforme_view(from, to, up);
	if (!mtx_eq(ist, soll))
	{
		printf("IST: \n");
		mtx_print_matrix(&ist, MAT4X4);
		printf("\n");
		printf("SOLL: \n");
		mtx_print_matrix(&soll, MAT4X4);
	}
	return(mtx_eq(ist, soll));
}
