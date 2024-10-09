/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:14 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:15 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_floats.h>
#include <ft_tuple.h>
#include <libft.h>

void	print_t(int fd, t_tuple t)
{
	(void)fd;
	fprintf(stdout, "x: %f\ny: %f\nz: %f\nw: %f\n", \
		t.x, t.y, t.z, t.w);
}
