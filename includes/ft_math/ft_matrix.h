
#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include <ft_tuple.h>

typedef int	t_fd;

typedef enum e_matrix_type
{
	MAT2X2 = 2,
	MAT3X3 = 3,
	MAT4X4 = 4
}	t_matrix_type;

typedef struct s_matrix
{
	float			m[4][4];//mat[row][col] indexed no matter the type
	t_matrix_type	type;
}	t_matrix;

// matrix_init.c
t_matrix	mtx_new_ident(t_matrix_type type);
t_matrix	mtx_get_rdm_m(t_matrix_type type);

// matrix_mult.c
t_tuple		mtx_mult_mt(t_matrix m, t_tuple tup);
t_matrix	mtx_mult_mm(t_matrix ma, t_matrix mb);

// matrix_mult_tests.c
bool		test_mtx_mult_mt(void);
bool		test_mtx_mult_mm(void);

// matrix_determinant.c
t_matrix	mtx_sub_matrix(t_matrix m, int remove_row, int remove_col);
double		mtx_det(t_matrix m);
double		mtx_cofactor(t_matrix m, int row, int col);

// matrix_determinant_tests.c
bool		test_mtx_sub_matrix(void);
bool		test_mtx_cofactor(void);
bool		test_mtx_det(void);

// Matrix minor
double		mtx_minor(t_matrix m, int row, int col);
int			test_mtx_minor(void);

// matrix_inverse.c
t_matrix	mtx_inverse(t_matrix m);
// test_mtx_inverse.c
bool		test_mtx_inverse(void);

// matrix_translation_scaling.c
t_matrix	mtx_translation(float x, float y, float z);
//TODO:
t_matrix	mtx_scale(float x, float y, float z);
t_matrix	mtx_skew(float xy, float xz, float yx, float yz, float zx, float zy);
// end TODO

// matrix_rotation.c
t_matrix	mtx_pitch(double theta);
t_matrix	mtx_roll(double theta);
t_matrix	mtx_yaw(double theta);

// test_mix.c
bool		test_matrix_mult_inverse(void);

// matrix_debug.c
void		mtx_print(t_fd fd, t_matrix m);
bool		mtx_eq(t_matrix ma, t_matrix mb);
bool		mtx_eq_roughly(t_matrix ma, t_matrix mb);

// matrix_other_tests.c
bool		test_mtx_eq(void);

// Matrix Transpose
t_matrix	mtx_transpose(t_matrix m);
int			test_mtx_transpose(void);

//Helper
int			mtx_get_matrix_dimension(t_matrix_type type);
void		mtx_print_matrix(void *matrix, t_matrix_type type);

//End Helper
#endif // MATRIX_H

