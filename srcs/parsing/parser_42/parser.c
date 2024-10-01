#include <main.h>
#include <ft_engine.h>

#define PARSER_OFFSET_SPHERE 0.0003
#define PARSER_OFFSET_PLANE 0.0005
#define PARSER_OFFSET_LIGHT 0.0007
#define PARSER_OFFSET_CAMERA 0.00011

#define PARSER_MEM_SIZE 10000
#define PARSER_HASH_PRIME 31
#define PARSER_HASH_SCALAR 1000

size_t	parser_hash_point(t_point point)
{
	size_t	hash;
	t_vec	vec;

	vec = sub_t(point, new_point(0, 0, 0));
	vec = mult_v(vec, PARSER_HASH_SCALAR);
	hash = ((size_t) (PARSER_HASH_PRIME * PARSER_HASH_PRIME * vec.x
		+ PARSER_HASH_PRIME * vec.y
		+ vec. x)) % PARSER_MEM_SIZE;
	return (hash);
}

size_t	parser_get_mem_count(size_t mem[PARSER_MEM_SIZE], t_point point)
{
	size_t	hash;

	hash = parser_hash_point(point);
	return (mem[hash]);
}

void	parser_inc_mem(size_t mem[PARSER_MEM_SIZE], t_point point)
{
	size_t	hash;

	hash = parser_hash_point(point);
	mem[hash]++;
}

t_point	handle_point_collision(size_t mem_points[PARSER_MEM_SIZE],
			t_point point, double obj_modulo_prime)
{
	double	collision_offset;

	collision_offset = obj_modulo_prime
		* parser_get_mem_count(mem_points, point);
	parser_inc_mem(mem_points, point);
	point = add_t(point,
			new_vec(collision_offset, collision_offset, collision_offset));
	return(point);
}

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
	if (*str == '-')
		str++;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str) && *str != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->y = str_to_float(str);
	if (*str == '-')
		str++;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str) && *str != '-')
		ft_error("parsing error", __FILE__, __LINE__, 100);
	ret->z = str_to_float(str);
	if (*str == '-')
		str++;
	while (*str && (*str == '.' || ft_isdigit(*str)))
		str++;
	while(*str && ft_iswhitespace(*str))
		str++;
	*str_ptr = str;
}

void	parse_camera(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
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

void	parse_light(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_light		light;
	t_point		origin;
	double		scalar;
	t_fcolor	color;

	printf("parsing light\n");
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
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&light);
}

void	parse_plane(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	t_plane		plane;
	t_point		point;
	t_vec		normal;
	t_fcolor	fcolor;
	t_vec		base_normal;
	t_vec		rotation_axis;
	double		angle;

	printf("parsing plane\n");
	line += 2;
	plane = eng_new_plane();

	point = new_point(0, 0, 0);
	str_to_tuple(line, &point, &line);
	point = handle_point_collision(mem_points, point, PARSER_OFFSET_PLANE);

	normal = new_vec(0, 0, 0);
	str_to_tuple(line, &normal, &line);
	normal = norm(normal);

	fcolor = new_fcolor(0, 0, 0, 1);
	str_to_fcolor(line, &fcolor, &line);
	plane.base_obj.material.fcolor = fcolor;
	base_normal = norm(new_vec(0, 1, 0));
	if (!eq_t(base_normal, normal))
	{
		rotation_axis = cross_prod(base_normal, normal);
		angle  = acos(dot_prod(base_normal, normal));
		eng_set_transform((t_obj *)&plane, mtx_rotation_axis_angle(rotation_axis, angle));
	}
	eng_set_transform((t_obj *)&plane, mtx_translate(point.x, point.y, point.z));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&plane);
}

void	parse_sphere(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
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
	
	eng_set_transform((t_obj *)&sph, mtx_scale(diameter / 2, diameter / 2,
		diameter / 2));
	eng_add_obj_to_world(&m_data->engine.world, (t_obj *)&sph);
}

void	parse_line(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
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
		parse_camera(m_data, line, mem_points);
	else if (*line == 'L')
		parse_light(m_data, line, mem_points);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(m_data, line, mem_points);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(m_data, line, mem_points);
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
	size_t	mem_points[PARSER_MEM_SIZE];

	ft_bzero(mem_points, sizeof mem_points);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Can not open file", __FILE__, __LINE__, errno);
	m_data->cleanup_data.fd = fd;
	line = get_next_line(fd, false);
	while (line)
	{
		parse_line(m_data, line, mem_points);
		free(line);
		line = get_next_line(fd, false);
	}
	close(fd);
	m_data->cleanup_data.fd = 0;
	get_next_line(fd, true);
	//eng_print_world(m_data->engine.world);
}
