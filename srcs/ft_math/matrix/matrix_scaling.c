/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scaling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:42 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:57:46 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>

t_matrix	mtx_scale(double x, double y, double z)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][0] = x;
	ret.m[1][1] = y;
	ret.m[2][2] = z;
	return (ret);
}

// TODO: 17.09.2024
t_matrix	mtx_scale_izi(t_tuple tuple)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][0] = tuple.x;
	ret.m[1][1] = tuple.y;
	ret.m[2][2] = tuple.z;
	return (ret);
}
