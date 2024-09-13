
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
float		mtx_cofactor(t_matrix m, int row, int col);

// matrix_determinant_tests.c
bool		test_mtx_sub_matrix(void);
bool		test_mtx_cofactor(void);

// matrix_debug.c
void		mtx_print(t_fd fd, t_matrix m);
bool		mtx_eq(t_matrix ma, t_matrix mb);

// matrix_other_tests.c
bool		test_mtx_eq(void);

//Helper
int			mtx_get_matrix_dimension(t_matrix_type type);
void		mtx_print_matrix(void *matrix, t_matrix_type type);

//End Helper


#endif // MATRIX_H

