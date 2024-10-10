/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_shearing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:38 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:35:41 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>

t_matrix	mtx_skew(struct s_skew para)
{
	t_matrix	ret;

	ret = mtx_new_ident(MAT4X4);
	ret.m[0][1] = para.xy;
	ret.m[0][2] = para.xz;
	ret.m[1][0] = para.yx;
	ret.m[1][2] = para.yz;
	ret.m[2][0] = para.zx;
	ret.m[2][1] = para.zy;
	return (ret);
}
