#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

void	mtx_print_error_msg(t_matrix pre, t_matrix ist, t_matrix soll)
{
	ft_fprintf(2, "Error: mtx_transpose()\n");
	mtx_print(2, pre);
	ft_fprintf(2, "resulted in matrix:\n");
	mtx_print(2, ist);
	ft_fprintf(2, "expected matrix:\n");
	mtx_print(2, soll);
}

int	test_mtx_transpose(void)
{
	t_matrix	ist;

	t_matrix	pre =
	{
		.m = {
			{0, 9, 3, 0},
			{9, 8, 0, 8},
			{1, 8, 5, 3},
			{0, 0, 5, 8}},
		.type = MAT4X4,
	};
	t_matrix	soll =
	{
		.m = {
			{0, 9, 1, 0},
			{9, 8, 8, 0},
			{3, 0, 5, 5},
			{0, 8, 3, 8}},
		.type = MAT4X4,
	};
	ist = mtx_transpose(pre);
	if (!mtx_eq(ist, soll))
	{
		mtx_print_error_msg(pre, ist, soll);
		return (0);
	}
	return (1);
}
