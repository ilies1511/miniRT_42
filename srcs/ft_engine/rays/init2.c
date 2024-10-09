/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:32 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:35:35 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <libft.h>

t_cone	eng_new_cone(void)
{
	t_cone	cone;

	cone.base_obj = eng_new_obj();
	cone.base_obj.type = OBJ_CONE;
	cone.max = INFINITY;
	cone.min = -INFINITY;
	cone.closed = false;
	return (cone);
}

t_cylinder	eng_new_cylinder(void)
{
	t_cylinder	cylinder;

	cylinder.base_obj = eng_new_obj();
	cylinder.base_obj.type = OBJ_CYLINDER;
	cylinder.max = INFINITY;
	cylinder.min = -INFINITY;
	cylinder.closed = false;
	return (cylinder);
}