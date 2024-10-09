/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:05 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:06 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_matrix.h>
#include <libft.h>

t_matrix	mtx_new_ident(t_matrix_type type)
{
	t_matrix	m;
	int			i;
	int			j;

	ft_bzero(&m, sizeof m);
	m.type = type;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[j][i] = 1.0;
			else
				m.m[j][i] = 0.0;
			j++;
		}
		i++;
	}
	return (m);
}
