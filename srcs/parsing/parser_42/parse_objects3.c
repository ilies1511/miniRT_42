/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:02:17 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 16:02:33 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

void	parse_plane(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_plane		plane;
	t_point		p;
	t_vec		normal;
	t_vec		rot_axis;
	double		angle;

	line += 2;
	plane = eng_new_plane();
	str_to_tuple(line, &p, &line, 1.0);
	p = handle_point_collision(mem_points, p, PARSER_OFFSET_PLANE);
	str_to_tuple(line, &normal, &line, 0.0);
	normal = norm(normal);
	str_to_fcolor(line, &plane.base_obj.material.fcolor, &line);
	if (!eq_t(norm(new_vec(0, 1, 0)), normal))
	{
		rot_axis = cross_prod(norm(new_vec(0, 1, 0)), normal);
		angle = acos(dot_prod(norm(new_vec(0, 1, 0)), normal));
		eng_set_transform((t_obj_ptr) & plane,
			mtx_rotation_axis_angle(rot_axis, angle));
	}
	eng_set_transform((t_obj_ptr) & plane, mtx_translate(p.x, p.y, p.z));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & plane);
}
