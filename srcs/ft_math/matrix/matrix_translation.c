/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:36 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:37 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>

t_matrix	mtx_translate_izi(t_tuple tuple)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] = tuple.x;
	ret.m[1][3] = tuple.y;
	ret.m[2][3] = tuple.z;
	return (ret);
}

t_matrix	mtx_translate(double x, double y, double z)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][3] = x;
	ret.m[1][3] = y;
	ret.m[2][3] = z;
	return (ret);
}
