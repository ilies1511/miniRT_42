/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:50 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:35:51 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <libft.h>

void	cal_disc_sqrt(t_cone_norm *n)
{
	if (!eq_f(n->disc, 0))
		n->sqrt_discriminant = sqrtl(n->disc);
	else
		n->sqrt_discriminant = 0;
}

void	cal_abc(t_cone_norm *n, t_ray ray)
{
	n->a = (ray.direct.x * ray.direct.x) - (ray.direct.y * ray.direct.y) + \
			(ray.direct.z * ray.direct.z);
	n->b = (2 * ray.origin.x * ray.direct.x) - \
		(2 * ray.origin.y * ray.direct.y) + (2 * ray.origin.z * ray.direct.z);
	n->c = (ray.origin.x * ray.origin.x) - (ray.origin.y * ray.origin.y) + \
		(ray.origin.z * ray.origin.z);
	n->two_a = (2 * n->a);
}

void	cal_intesects(t_cone_norm *n)
{
	if (!eq_f(n->a, 0))
	{
		n->t0 = (-n->b - n->sqrt_discriminant) / n->two_a;
		n->t1 = (-n->b + n->sqrt_discriminant) / n->two_a;
	}
	else if (eq_f(n->a, 0) && !eq_f(n->b, 0))
	{
		n->t0 = -n->c / (2 * n->b);
		n->t1 = n->t0;
	}
	else
		rt_assert(false, __FILE__, __LINE__, \
			"Impossible Case for Cone Intersection");
}

void	swap_double_co(t_cone_norm *n)
{
	double	temp;

	temp = n->t0;
	n->t0 = n->t1;
	n->t1 = temp;
}

/*
Optional(cap intersects) at very endeng_intersc_ray_cone_caps
(intersecs, ray, cone);
*/
void	add_intersects(t_cone_norm *n, t_intersc_arr *intersecs, t_ray ray,
			t_cone *cone)
{
	if (n->t0 > n->t1)
		swap_double_co(n);
	n->y0 = ray.origin.y + n->t0 * ray.direct.y;
	if (cone->min < n->y0 && n->y0 < cone->max)
		eng_add_intersc(intersecs, (t_obj_ptr)cone, n->t0);
	n->y1 = ray.origin.y + n->t1 * ray.direct.y;
	if (cone->min < n->y1 && n->y1 < cone->max)
		eng_add_intersc(intersecs, (t_obj_ptr)cone, n->t1);
}
