/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:35 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:34:36 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <ft_refraction.h>
#include <main.h>
#include <ft_matrix.h>
#include <libft.h>

static inline bool	total_internal_reflect(double sin2_t)
{
	if (sin2_t > 1.0)
		return (true);
	return (false);
}

// returns the reflectance (amount of the light that is reflected)
double	ref_schlick(t_computation comp)
{
	double	cos_eye;
	double	n;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos_eye = dot_prod(norm(comp.eye_v), norm(comp.normal_v));
	if (comp.n1 > comp.n2)
	{
		n = comp.n1 / comp.n2;
		sin2_t = n * n * (1.0 - cos_eye * cos_eye);
		if (total_internal_reflect(sin2_t))
			return (1.0);
		cos_t = sqrt(1.0 - sin2_t);
		cos_eye = cos_t;
	}
	r0 = (comp.n1 - comp.n2) / (comp.n1 + comp.n2);
	r0 *= r0;
	return (r0 + (1.0 - r0) * pow(1.0 - cos_eye, 5));
}
