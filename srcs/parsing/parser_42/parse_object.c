#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

//TODO: not mentioned in subject
void	parse_camera(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_point	origin;
	t_point	to;
	t_vec	up;
	double	fov;

	up = new_vec(0, 1, 0);
	line++;
	origin = new_point(0, 0, 0);
	to = new_point(0, 0, 0);
	str_to_tuple(line, &origin, &line);
	parser_inc_mem(mem_points, origin);
	str_to_tuple(line, &to, &line);
	parser_inc_mem(mem_points, to);
	while (ft_iswhitespace(*line))
		line++;
	if (!ft_isdigit(*line) && *line != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	fov = str_to_float(line);
	m_data->engine.camera = eng_new_camera(m_data->engine.canvas.width,
			m_data->engine.canvas.height, fov);
	eng_set_transform((t_obj_ptr)&m_data->engine.camera, sc_transforme_view(
			origin, to, up));
}

void	parse_light(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_light		light;
	t_point		origin;
	double		scalar;
	t_fcolor	color;

	line++;
	origin = new_point(0, 0, 0);
	str_to_tuple(line, &origin, &line);
	origin = handle_point_collision(mem_points, origin, PARSER_OFFSET_LIGHT);
	if (!ft_isdigit(*line) && *line != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	scalar = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;
	color = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &color, &line);
	color = scale_fcolor(color, scalar);
	light = eng_point_light(color, origin);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr)&light);
}

void	parse_plane(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_plane		plane;
	t_point		p;
	t_vec		normal;
	t_vec		rot;
	double		angle;

	line += 2;
	plane = eng_new_plane();
	p = new_point(0, 0, 0);
	str_to_tuple(line, &p, &line);
	p = handle_point_collision(mem_points, p, PARSER_OFFSET_PLANE);
	normal = new_vec(0, 0, 0);
	str_to_tuple(line, &normal, &line);
	normal = norm(normal);
	plane.base_obj.material.fcolor = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &plane.base_obj.material.fcolor, &line);
	if (!eq_t(norm(new_vec(0, 1, 0)), normal))
	{
		rot = cross_prod(norm(new_vec(0, 1, 0)), normal);
		angle = acos(dot_prod(norm(new_vec(0, 1, 0)), normal));
		eng_set_transform((t_obj_ptr)&plane, mtx_rotation_axis_angle(rot, angle));
	}
	eng_set_transform((t_obj_ptr)&plane, mtx_translate(p.x, p.y, p.z));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr)&plane);
}

void	parse_sphere(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_sphere	sph;
	t_point		origin;
	double		diameter;
	t_fcolor	fcolor;

	line += 2;
	sph = eng_new_sphere();
	origin = new_point(0, 0, 0);
	str_to_tuple(line, &origin, &line);
	origin = handle_point_collision(mem_points, origin, PARSER_OFFSET_PLANE);
	if (!ft_isdigit(*line))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	diameter = str_to_float(line);
	if (*line == '-')
		line++;
	while (line && !ft_iswhitespace(*line))
		line++;
	fcolor = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &fcolor, &line);
	sph.base_obj.material.fcolor = fcolor;
	eng_set_transform((t_obj_ptr)&sph, mtx_scale(diameter / 2, diameter / 2,
			diameter / 2));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr)&sph);
}
