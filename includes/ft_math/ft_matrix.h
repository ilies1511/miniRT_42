
#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include <ft_tuple.h>

typedef int	t_fd;

//typedef float	t_mat2x2[2][2];//mat[row][col]
//typedef float	t_mat3x3[3][3];//mat[row][col]
//typedef float	t_mat4x4[4][4];//mat[row][col]

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

bool		eq_m(t_matrix ma, t_matrix mb);
t_matrix	new_ident_m(t_matrix_type type);
t_tuple		mult_mt(t_matrix m, t_tuple tup);
t_matrix	mult_mm(t_matrix ma, t_matrix mb);
// tests
t_matrix	get_rad_m(void);
void	print_m(t_fd fd, t_matrix m);
bool	test_eq_m(void);
bool	test_mult_mt(void);

// rotation_matrix.c
t_matrix	pitch_matrix(double theta);
t_matrix	yaw_matrix(double theta);
t_matrix	roll_matrix(double theta);
#endif // MATRIX_H
