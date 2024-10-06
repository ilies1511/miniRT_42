#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

static void	set_transform_cylinder(t_cylinder *cyl, t_vec axis, double radius,
	t_point center)
{
	t_matrix	rotation;
	t_matrix	scaleing_radius;
	t_matrix	translation;
	t_matrix	transformation;
	t_vec		rot;
	double		angle;

	rotation = mtx_new_ident(MAT4X4);
	scaleing_radius = mtx_scale(radius, 1, radius);
	translation = mtx_translate(center.x, center.y, center.z);
	transformation = mtx_new_ident(MAT4X4);
	if (eq_t(norm(new_vec(0, -1, 0)), axis))
		rotation = mtx_rotation_x(M_PI);
	else if (!eq_t(norm(new_vec(0, 1, 0)), axis))
	{
		rot = cross_prod(norm(new_vec(0, 1, 0)), axis);
		angle = acos(dot_prod(norm(new_vec(0, 1, 0)), axis));
		rotation = mtx_rotation_axis_angle(rot, angle);
	}
	transformation = mtx_mult_mm(transformation, translation);
	transformation = mtx_mult_mm(transformation, rotation);
	transformation = mtx_mult_mm(transformation, scaleing_radius);
	eng_set_transform((t_obj_ptr)cyl, transformation);
}

void	parse_cylinder(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_cylinder	cyl;
	t_point		center;
	t_vec		axis;
	double		radius;
	double		height;

	line += 2;
	cyl = eng_new_cylinder();
	cyl.closed = true;
	str_to_tuple(line, &center, &line, 1.0);
	center = handle_point_collision(mem_points, center, PARSER_OFFSET_CYLINDER);
	str_to_tuple(line, &axis, &line, 0.0);
	axis = norm(axis);
	if (!ft_isdigit(*line))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	radius = str_to_float(line) / 2;
	skip_float(&line);
	height = str_to_float(line);
	cyl.max = height / 2;
	cyl.min = -height / 2;
	skip_float(&line);
	str_to_fcolor(line, &cyl.base_obj.material.fcolor, &line);
	set_transform_cylinder(&cyl, axis, radius, center);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj_ptr)&cyl);
}
