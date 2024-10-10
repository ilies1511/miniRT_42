/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:36 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:31:37 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

void	parse_ambient(t_main *m_data, char *line)
{
	double		scalear;
	t_fcolor	color;

	while (line && !ft_isdigit(*line))
		line++;
	scalear = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;
	str_to_fcolor(line, &color, &line);
	m_data->engine.world.ambient42 = scale_fcolor(color, scalear);
}

#ifndef CAMERA_GOOD

//note: up not mentioned in subject so it's fixed to (0, 1, 0)
void	parse_camera(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_point	origin;
	t_vec	direct;
	t_vec	up;
	double	fov;
	t_point	to;

	up = norm(new_vec(0, 1, 0));
	str_to_tuple(++line, &origin, &line, 1.0);
	parser_inc_mem(mem_points, origin);
	str_to_tuple(line, &direct, &line, 0.0);
	to = add_t(origin, norm(direct));
	if (eq_t(norm(direct), up) || eq_t(norm(direct), norm(new_vec(0, -1, 0))))
		up = norm(new_vec(0, 0, 1));
	parser_inc_mem(mem_points, to);
	skip_whitespace(&line);
	if (!ft_isdigit(*line) && *line != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	fov = str_to_float(line);
	if (fov > 170 || fov < 1)
		parser_error("Error: fov out of range", __FILE__, __LINE__, 100);
	m_data->engine.camera = eng_new_camera(m_data->engine.canvas.width,
			m_data->engine.canvas.height, fov / 180 * M_PI);
	if (eq_t(origin, to))
		parser_error("camera orgin and camera look at can not be eaqual",
			__FILE__, __LINE__, 100);
	eng_set_transform((t_obj_ptr) & m_data->engine.camera, sc_transforme_view(
			origin, to, up));
}
#else

//note: up not mentioned in subject so it's fixed to (0, 1, 0)
void	parse_camera(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_point	origin;
	t_vec	direct;
	t_vec	up;
	double	fov;
	t_point	to;

	up = norm(new_vec(0, 1, 0));
	str_to_tuple(++line, &origin, &line, 1.0);
	parser_inc_mem(mem_points, origin);
	str_to_tuple(line, &to, &line, 1.0);
	direct = norm(sub_t(to, origin));
	if (eq_t(norm(direct), up) || eq_t(norm(direct), norm(new_vec(0, -1, 0))))
		up = norm(new_vec(0, 0, 1));
	parser_inc_mem(mem_points, to);
	skip_whitespace(&line);
	if (!ft_isdigit(*line) && *line != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	fov = str_to_float(line);
	m_data->engine.camera = eng_new_camera(m_data->engine.canvas.width,
			m_data->engine.canvas.height, fov / 180 * M_PI);
	if (eq_t(origin, to))
		parser_error("camera orgin and camera look at can not be eaqual",
			__FILE__, __LINE__, 100);
	eng_set_transform((t_obj_ptr) & m_data->engine.camera, sc_transforme_view(
			origin, to, up));
}
#endif //CAMERA_GOOD

void	parse_light(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_light		light;
	t_point		origin;
	double		scalar;
	t_fcolor	color;

	line++;
	str_to_tuple(line, &origin, &line, 1.0);
	origin = handle_point_collision(mem_points, origin, PARSER_OFFSET_LIGHT);
	if (!ft_isdigit(*line) && *line != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	scalar = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;
	str_to_fcolor(line, &color, &line);
	color = scale_fcolor(color, scalar);
	light = eng_point_light(color, origin);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & light);
}

void	parse_spot_light(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_light		light;
	t_point		origin;
	t_point		look_at;
	double		scalar;
	t_fcolor	color;

	line++;
	line++;
	str_to_tuple(line, &origin, &line, 1.0);
	origin = handle_point_collision(mem_points, origin, PARSER_OFFSET_LIGHT);
	if (!ft_isdigit(*line) && *line != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	scalar = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;
	str_to_fcolor(line, &color, &line);
	color = scale_fcolor(color, scalar);
	str_to_tuple(line, &look_at, &line, 1.0);
	look_at = handle_point_collision(mem_points, look_at, PARSER_OFFSET_LIGHT);
	light = eng_spot_light(color, origin, look_at, 20.0);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr) & light);
}

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
