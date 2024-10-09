/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_wave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:29 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:36:31 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_bump_map.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>

t_bump	*bump_wave(void)
{
	t_bump	*bump;

	bump = bump_new_bump();
	bump->type = BUMP_WAVE;
	return (bump);
}

/*
	Init for varibales, that are used for cylinder
*/
static void	init_bumpwave_norm(t_bump_norm *n, t_point point)
{
	const double	init_amplitutes[5] = {0.01, 0.05, 0.03, 0.02, 0.01};
	const double	init_wavelengths[5] = {30.0, 15.0, 10.0, 5.0, 2.5};
	const double	init_directions[5][2] = \
	{
	{1.0, 0.0},
	{0.7, 0.7},
	{0.0, 1.0},
	{-0.7, 0.7},
	{-1.0, 0.0}
	};

	n->d_dx = 0.0;
	n->d_dy = 0.0;
	n->d_dz = 0.0;
	n->x = point.x;
	n->z = point.z;
	ft_memcpy(n->amplitudes, init_amplitutes, sizeof init_amplitutes);
	ft_memcpy(n->wavelengths, init_wavelengths, sizeof init_wavelengths);
	ft_memcpy(n->directions, init_directions, sizeof init_directions);
}

static void	norm_koordinates(t_bump_norm *n)
{
	n->dir_length = sqrt((n->dir_x * n->dir_x) + (n->dir_z * n->dir_z));
	n->dir_x = n->dir_x / n->dir_length;
	n->dir_z = n->dir_z / n->dir_length;
}

// t_bump_norm		n = {.num_waves = 5};
t_vec	bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal)
{
	const int		num_waves = 5;
	t_bump_norm		n;

	init_bumpwave_norm(&n, point);
	n.i = -1;
	while (++n.i < num_waves)
	{
		n.amplitude = n.amplitudes[n.i];
		n.wavelength = n.wavelengths[n.i];
		n.k = 2.0 * M_PI / n.wavelength;
		n.dir_x = n.directions[n.i][0];
		n.dir_z = n.directions[n.i][1];
		norm_koordinates(&n);
		n.dot = n.k * (n.dir_x * n.x + n.dir_z * n.z);
		n.cos_dot = cos(n.dot);
		n.sin_dot = sin(n.dot);
		n.d_dx += n.amplitude * n.k * n.dir_x * n.cos_dot;
		n.d_dy += n.amplitude * n.k * n.sin_dot;
		n.d_dz += n.amplitude * n.k * n.dir_z * n.cos_dot;
	}
	n.perturbed_normal = norm(new_vec(-n.d_dx, \
		base_normal.y - n.d_dy, -n.d_dz));
	return (n.perturbed_normal);
}
