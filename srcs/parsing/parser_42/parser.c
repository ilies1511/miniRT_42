#include <main.h>

// retusn false on invalid tuple str
void	str_to_tuple(char *str, t_tuple *ret, char **str_ptr)
{
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!ft_isdigit(*str) && *str != '-')
	{
		ft_error("parsing error", __FILE__, __LINE__, 100);
	}
	ret->x = str_to_float(str);
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str) && *str != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->y = str_to_float(str);
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str) && *str != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->z = str_to_float(str);
	while (*str && (*str == '.' || ft_isdigit(*str)))
		str++;
	while(*str && ft_iswhitespace(*str))
		str++;
	*str_ptr = str;
}

void	parse_camera(t_main *m_data, char *line)
{
	t_point	origin;
	t_point	to;
	t_vec	up = new_vec(0, 1, 0);//TODO: not mentioned in subject
	double	fov;

	printf("parsing camera\n");
	line++;
	origin = new_point(0, 0, 0);
	to = new_point(0, 0, 0);
	str_to_tuple(line, &origin, &line);
	str_to_tuple(line, &to, &line);
	print_t(1, origin);
	print_t(1, to);
	while (ft_iswhitespace(*line))
		line++;
	if (!ft_isdigit(*line) && *line != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	fov = str_to_float(line);
	m_data->engine.camera = eng_new_camera(m_data->engine.canvas.width,
			m_data->engine.canvas.height, fov);
	eng_set_transform((t_obj *)&m_data->engine.camera, sc_transforme_view(
			origin, to, up));
}

void	str_to_fcolor(char *str, t_fcolor *ret, char **str_ptr)
{
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!ft_isdigit(*str))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->r = str_to_float(str) / 255;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->g = str_to_float(str) / 255;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->b = str_to_float(str) / 255;
	while (*str && (ft_isdigit(*str) || *str == '.'))
		str++;
	while(*str && ft_iswhitespace(*str))
		str++;
	*str_ptr = str;
}

void	parse_light(t_main *m_data, char *line)
{
	t_light		light;
	t_point		origin;
	double		scalar;
	t_fcolor	color;

	printf("parsing light\n");
	line++;
	origin = new_point(0, 0, 0);
	color = new_fcolor(0, 0, 0, 1);
	str_to_tuple(line, &origin, &line);

	if (!ft_isdigit(*line))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	scalar = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;

	str_to_fcolor(line, &color, &line);

	color = scale_fcolor(color, scalar);
	light = eng_point_light(color, origin);
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&light);
}


t_matrix mtx_rotation_axis_angle(t_vec axis, double angle) {
	axis = norm(axis);
	double cos_a = cos(angle);
	double sin_a = sin(angle);
	double one_minus_cos_a = 1 - cos_a;

	t_matrix rot = {
		.m[0] = {
			cos_a + axis.x * axis.x * one_minus_cos_a,
			axis.x * axis.y * one_minus_cos_a - axis.z * sin_a,
			axis.x * axis.z * one_minus_cos_a + axis.y * sin_a
		},
		.m[1] = {
			axis.y * axis.x * one_minus_cos_a + axis.z * sin_a,
			cos_a + axis.y * axis.y * one_minus_cos_a,
			axis.y * axis.z * one_minus_cos_a - axis.x * sin_a
		},
		.m[2] = {
			axis.z * axis.x * one_minus_cos_a - axis.y * sin_a,
			axis.z * axis.y * one_minus_cos_a + axis.x * sin_a,
			cos_a + axis.z * axis.z * one_minus_cos_a
		},
		.m[3] = {0,0,0,1},
		.type = MAT4X4,
	};
	return rot;
}

//TODO: figure out how to correctly take a normal and convert it to the
//correct transformation matrix
void	parse_plane(t_main *m_data, char *line)
{
	return ;
	t_plane		plane;
	t_point		point;
	t_vec		normal;
	t_fcolor	fcolor;
	t_vec		base_normal;

	printf("parsing plane\n");
	line += 2;
	plane = eng_new_plane();

	point = new_point(0, 0, 0);
	str_to_tuple(line, &point, &line);

	normal = new_vec(0, 0, 0);
	str_to_tuple(line, &normal, &line);
	normal = norm(normal);

	fcolor = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &fcolor, &line);
	plane.base_obj.material.fcolor = fcolor;

	base_normal = norm(new_vec(0, 1, 0));
	
	if (!eq_t(base_normal, normal))
	{
		t_vec	rotation_axis = cross_prod(base_normal, normal);
		double angle  = acos(dot_prod(base_normal, normal));

		eng_set_transform((t_obj *)&plane, mtx_rotation_axis_angle(rotation_axis, angle));
	}
	eng_set_transform((t_obj *)&plane, mtx_translate(point.x, point.y, point.z));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&plane);
}

void	parse_sphere(t_main *m_data, char *line)
{
	t_sphere	sph;
	t_point		origin;
	double		diameter;
	t_fcolor	fcolor;

	printf("parsing sphere\n");
	line += 2;
	sph = eng_new_sphere();
	origin = new_point(0, 0, 0);
	str_to_tuple(line, &origin, &line);

	if (!ft_isdigit(*line))
		ft_error("parsing error", __FILE__, __LINE__, 100);
	diameter = str_to_float(line);
	while (line && !ft_iswhitespace(*line))
		line++;
	
	fcolor = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &fcolor, &line);
	sph.base_obj.material.fcolor = fcolor;

	eng_set_transform((t_obj *)&sph, mtx_scale(diameter / 2, diameter / 2,
		diameter / 2));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&sph);
}

void	parse_line(t_main *m_data, char *line)
{
	while (ft_iswhitespace(*line))
		line++;
	if (*line == 'A')
	{
		//TODO: needs small refactor of t_material and eng_lighting
		//will break a bunch of tests thus should be done in the end
		//should not be hard
	}
	else if (*line == 'C')
		parse_camera(m_data, line);
	else if (*line == 'L')
		parse_light(m_data, line);
	else if (line[0] == 'p' && line[1] == 'l')
	{
		//TODO: read pase_plane todo, not simple math problem
		parse_plane(m_data, line);
	}
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(m_data, line);
	else if (line[0] == 'c' && line[1] == 'y')
	{
		//TODO:
	}
}

//TODO: validate path file type
void	parser(t_main *m_data, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Can not open file", __FILE__, __LINE__, errno);
	m_data->cleanup_data.fd = fd;
	line = get_next_line(fd, false);
	while (line)
	{
		parse_line(m_data, line);
		free(line);
		line = get_next_line(fd, false);
	}
	close(fd);
	m_data->cleanup_data.fd = 0;
	get_next_line(fd, true);
}
