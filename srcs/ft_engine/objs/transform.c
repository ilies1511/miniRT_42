/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:23 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:36:24 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <libft.h>
#include <ft_matrix.h>
#include <ft_engine.h>
#include <libft.h>

// tmp var in case in == ret
static void	transform_ray(t_ray *in, t_ray *ret)
{
	t_ray	tmp;

	tmp = eng_new_ray(in->origin, in->direct);
	tmp.origin = mtx_mult_mt(in->base_obj.transform, in->origin);
	tmp.direct = mtx_mult_mt(in->base_obj.transform, in->direct);
	*ret = tmp;
}

//ret->origin = mtx_mult_mt(in->base_obj.transform, in->origin);
static void	transform_sphere(t_sphere *in, t_sphere *ret)
{
	(void)in;
	*ret = eng_new_sphere();
}

void	eng_transform(t_obj_ptr in, t_obj_ptr ret)
{
	if (in->type == OBJ_RAY)
		transform_ray((t_ray *)in, (t_ray *)ret);
	else if (in->type == OBJ_SPHERE)
		transform_sphere((t_sphere *)in, (t_sphere *)ret);
	else
		rt_assert(0, __FILE__, __LINE__, "Error: eng_transform: Invalid type");
}
