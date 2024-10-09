/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:09 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:46:16 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRIX_H
# define FT_MATRIX_H

# include <stdbool.h>
# include <ft_tuple.h>

typedef int	t_fd;

typedef enum e_matrix_type
{
	MAT2X2 = 2,
	MAT3X3 = 3,
	MAT4X4 = 4
}	t_matrix_type;

//mat[row][col] indexed no matter the type
typedef struct s_matrix
{
	double			m[4][4] __attribute__((aligned(16)));
	t_matrix_type	type;
}					t_matrix;

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

// matrix_inverse.c
t_matrix	mtx_inverse(t_matrix m);
// test_mtx_inverse.c

// matrix_translate_scaling.c
t_matrix	mtx_translate(double x, double y, double z);
t_matrix	mtx_translate_izi(t_tuple tuple);

t_matrix	mtx_scale(double x, double y, double z);

// Matrix Skew aka Shearing
struct s_skew
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
};
t_matrix	mtx_skew(struct s_skew para);

// matrix_rotation.c
// t_matrix	mtx_pitch(double theta);
// t_matrix	mtx_roll(double theta);
// t_matrix	mtx_yaw(double theta);
t_matrix	mtx_rotation_x(double theta);
t_matrix	mtx_rotation_y(double theta);
t_matrix	mtx_rotation_z(double theta);
t_matrix	mtx_rotation_axis_angle(t_vec axis, double angle);

// test_mix.c

// matrix_debug.c
void		mtx_print(t_fd fd, t_matrix m);
bool		mtx_eq(t_matrix ma, t_matrix mb);
bool		mtx_eq_roughly(t_matrix ma, t_matrix mb);

// matrix_other_tests.c
bool		test_mtx_eq(void);

// Matrix Transpose
t_matrix	mtx_transpose(t_matrix m);

// Matrix Scaling
t_matrix	mtx_scale_izi(t_tuple tuple);

#endif // FT_MATRIX_H
