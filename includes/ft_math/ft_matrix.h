
#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include <ft_tuple.h>

typedef float	t_mat2x2[2][2];//mat[row][col]
typedef float	t_mat3x3[3][3];//mat[row][col]
typedef float	t_mat4x4[4][4];//mat[row][col]
typedef double	t_double_mat4x4[4][4];//mat[row][col]
typedef int	t_fd;

// to avoid duplication: when possibe fucntions should take a t_matrix_type
// to determine the specific operation. If duplication would be simpler
// we should choose duplication tho
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
// this could be simply returned and copied with '=' (mat_a = mat_b)
// but every acces would be something like mat.mat[row][col]
// instead of mat[row][col], but this would need to use ft_memcpy for a simple '='
// and a pointer to pass data as a return val...
// IDK both suck in their way
// for now these defitions assume the first matrix type

//Helper
int		mtx_get_matrix_dimension(t_matrix_type type);
// void	mtx_print_matrix(float **matrix, t_matrix_type type);
// void	mtx_print_matrix(t_mat2x2 *matrix, t_matrix_type type);
// void	mtx_print_matrix(float ***matrix, t_matrix_type type);
void	mtx_print_matrix(void *matrix, t_matrix_type type);

//End Helper

t_matrix	new_ident_m(t_matrix_type type);
bool		eq_m(t_matrix ma, t_matrix mb);
t_tuple		mult_mt(t_matrix m, t_tuple tup);
t_matrix	mult_mm(t_matrix ma, t_matrix mb);
t_matrix	get_rdm_m(t_matrix_type type);
void		print_m(t_fd fd, t_matrix m);
bool		test_eq_m(void);
bool		test_mult_mt(void);


// void		print_mat(float *mat , t_matrix_type type);
// bool		eq_m(float *ma, float *mb);
// void		mult_mat(t_mat4x4 ma, t_mat4x4 mb, float *ret);

// t_tuple		mult_mat_tup(t_mat4x4 mat, t_tuple tup);
// void		fill_ident_mat(float *ret);
// void		transpose_mat(t_mat4x4 mat, float *ret);
// void		inverse_mat(t_mat4x4 mat, float *ret);

//..many more functions missing still
#endif // MATRIX_H

