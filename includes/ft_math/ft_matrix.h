
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

typedef union u_matrix
{
	struct
	{
		float			m[4][4];//mat[row][col] indexed no matter the type
		t_matrix_type	type;
	};
	t_vec				base_vecs[4];
}	__attribute__((packed))t_matrix;

bool		eq_m(t_matrix ma, t_matrix mb);
t_matrix	new_ident_m(t_matrix_type type);
t_tuple		mult_mt(t_matrix m, t_tuple tup);
t_matrix	mult_mm(t_matrix ma, t_matrix mb);
// tests
t_matrix	get_random_matrix(void);
void	print_m(t_fd fd, t_matrix m);
bool	test_eq_m(void);
bool	test_mult_mt(void);

#endif // MATRIX_H
