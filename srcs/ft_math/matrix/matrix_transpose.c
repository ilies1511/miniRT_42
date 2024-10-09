/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:33 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:34 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

t_matrix	mtx_transpose(t_matrix m)
{
	t_matrix	transposed_m;
	int			i;
	int			k;

	transposed_m.type = m.type;
	i = 0;
	while (i < (int)m.type)
	{
		k = 0;
		while (k < (int)m.type)
		{
			transposed_m.m[k][i] = m.m[i][k];
			k++;
		}
		i++;
	}
	return (transposed_m);
}
