#include <main.h>
#include "ft_matrix.h"

int	mtx_get_matrix_dimension(t_matrix_type type)
{
	// Da MAT2X2, MAT3x3, MAT4x4 fortlaufend sind, können wir einfach 2 addieren
	return (type + 2);
}

// Funktion zum Drucken der Matrix
void	mtx_print_matrix(void *matrix, t_matrix_type type)
{
	int		dim;
	int		i;
	int		j;

	dim = mtx_get_matrix_dimension(type);
	if (dim <= 0 || matrix == NULL)
	{
		printf("Invalid matrix or type.\n");
		return ;
	}
	float(*mat)[dim] = matrix;
	i = 0;
	while (i < dim)
	{
		printf("[ ");
		j = 0;
		while (j < dim)
		{
			printf("%f", mat[i][j]);
			if (j < dim - 1)
				printf(" ");
			j++;
		}
		printf(" ]\n");
		i++;
	}
}
// void	mtx_print_matrix(t_mat2x2 *matrix, t_matrix_type type)
// {
// 	int	dim;
// 	int	i;
// 	int	j;

// 	dim = mtx_get_matrix_dimension(type);
// 	if (dim <= 0 || matrix == NULL)
// 	{
// 		printf("Invalid matrix or type.\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (i < dim)
// 	{
// 		printf("[ ");
// 		j = 0;
// 		while (j < dim)
// 		{
// 			printf("%f", matrix[i][j]);
// 			if (j < dim - 1)
// 				printf(" ");
// 			j++;
// 		}
// 		printf(" ]\n");
// 		i++;
// 	}
// }
