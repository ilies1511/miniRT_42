#include <main.h>

char	*get_next_line(int fd, bool cleanup);

char	*skip_header(char *str)
{
	while (*str && *str != '=')
		(str)++;
	if (*str)
		str++;
	while (ft_iswhitespace(*str))
		(str)++;
	return (str);
}

bool	parse_rotation(char *key, char *val, t_obj_ptr obj)
{
	if (!ft_strncmp("ROTATION_X", key, ft_strlen("ROTATION_X")))
		eng_set_transform(obj, mtx_rotation_x(str_to_float(val) / 180 * M_PI));
	else if (!ft_strncmp("ROTATION_Y", key, ft_strlen("ROTATION_Y")))
		eng_set_transform(obj, mtx_rotation_x(str_to_float(val) / 180 * M_PI));
	else if (!ft_strncmp("ROTATION_Z", key, ft_strlen("ROTATION_Z")))
		eng_set_transform(obj, mtx_rotation_x(str_to_float(val) / 180 * M_PI));
	else
		return (false);
	return (true);
}

bool	parse_argb(char *key, char *val, t_fcolor *color)
{
	if (ft_strlen(key) < 3)
			return (false);
	if (*key == 'R' && (ft_iswhitespace(key[1]) || key[1] == '='))
		color->r = str_to_float(val) / 255.0;
	else if (*key == 'G' && (ft_iswhitespace(key[1]) || key[1] == '='))
		color->g = str_to_float(val) / 255.0;
	else if (*key == 'B' && (ft_iswhitespace(key[1]) || key[1] == '='))
		color->b = str_to_float(val) / 255.0;
	else if (*key == 'A' && (ft_iswhitespace(key[1]) || key[1] == '='))
		color->a = str_to_float(val);
	else
		return (false);
	print_fcolor("after entering argb: ", *color);
	return (true);
}

bool parse_radius(t_vec *radius, char *key, char *value)
{
	if (!ft_strncmp("RADIUS_X", key, ft_strlen("RADIUS_X")))
		radius->x = str_to_float(value);
	else if (!ft_strncmp("RADIUS_Y", key, ft_strlen("RADIUS_Y")))
		radius->y = str_to_float(value);	
	else if (!ft_strncmp("RADIUS_Z", key, ft_strlen("RADIUS_Y")))
		radius->z = str_to_float(value);
	else if (!ft_strncmp("RADIUS", key, ft_strlen("RADIUS")))
	{
		radius->x = str_to_float(value);
		radius->y = radius->x;
		radius->z = radius->x;
	}
	else
		return (false);
	return (true);
}

/*
	t_pattern	*pattern;
	t_fcolor	fcolor;				DONE
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	t_bump		*bump;
 */
t_material	parse_material(int fd)
{
	t_material	material;
	char		*line;
	char		*key;
	char		*value;

	material = eng_new_material();
	line = get_next_line(fd, 0);
	if (!line)
		ft_error("Parser error: unexpected EOF in material ('{') expected",
			__FILE__, __LINE__, 100);
	free(line);
	line = get_next_line(fd, 0);
	while (line && *line != '}')
	{
		//TODO: logic to parse material here
		key = line;
		skip_whitespace(&key);
		value = skip_header(key);
		parse_argb(key, value, &material.fcolor);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!line)
		ft_error("Parser error: unexpected EOF in material ('{') expected",
			__FILE__, __LINE__, 100);
	free(line);
	return (material);
}

void	new_parse_camera(int fd, t_main *m_data, t_camera *camera)
{
	double	fov;
	char	*line;
	t_point	origin;
	t_point	to;
	t_vec	up;
	char	*value;
	char	*key;

	origin = new_point(0, 0, -1);
	to = new_point(0, 0, -1);
	up = new_vec(0, 1, 0);
	fov = 60.0;
	line = get_next_line(fd, 0);
	while (line)
	{
		key = line;
		skip_whitespace(&key);
		value = skip_header(key);
		if (!ft_strncmp(key, "FOV", ft_strlen("FOV")))
			fov = str_to_float(value);
		else if (!ft_strncmp(key, "ORIGIN", ft_strlen("ORIGIN")))
			str_to_tuple(value, &origin, &value, 1.0);
		else if (!ft_strncmp(key, "TO", ft_strlen("TO")))
			str_to_tuple(value, &to, &value, 1.0);
		else if (!ft_strncmp(key, "UP", ft_strlen("UP")))
			str_to_tuple(value, &up, &value, 1.0);
		free(line);
		line = get_next_line(fd, 0);
	}
	origin = add_t(origin, new_vec(EPSILON, EPSILON, EPSILON));
	*camera = eng_new_camera(m_data->engine.canvas.width,
		m_data->engine.canvas.height, fov / 180.0 * M_PI);
	eng_set_transform((t_obj_ptr) & m_data->engine.camera, sc_transforme_view(
			origin, to, up));
}

void	new_parse_plane(int fd, t_world *world)
{
	char		*line;
	t_point		origin;
	char		*value;
	char		*key;
	t_plane		plane;
	t_vec		normal;
	t_vec		rot;
	double		angle;

	origin = new_point(0, 0, 0);
	plane = eng_new_plane();
	line = get_next_line(fd, 0);
	while (line)
	{
		key = line;
		skip_whitespace(&key);
		value = skip_header(key);
		if (!ft_strncmp("ORIGIN", key, ft_strlen("ORIGIN")))
			str_to_tuple(value, &origin, &value, 1.0);
		else if (!ft_strncmp("MATERIAL", key, ft_strlen("MATERIAL")))
			plane.base_obj.material = parse_material(fd);
		else if (!ft_strncmp("NORMAL", key, ft_strlen("NORMAL")))
		{
			str_to_tuple(value, &normal, &value, 0.0);
			normal = norm(normal);
			if (!eq_t(normal, norm(new_vec(0, 1, 0))))
			{
				rot = cross_prod(norm(new_vec(0, 1, 0)), normal);
				angle = acos(dot_prod(norm(new_vec(0, 1, 0)), normal));
				eng_set_transform((t_obj_ptr) & plane,
					mtx_rotation_axis_angle(rot, angle));
			}
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	eng_set_transform((t_obj_ptr) & plane, mtx_translate(origin.x, origin.y,
			origin.z));
	eng_add_obj_to_world(world, (t_obj_ptr) & plane);
}

void	new_parse_sphere(int fd, t_world *world)
{
	char		*line;
	t_point		origin;
	char		*value;
	t_vec		radius;
	t_sphere	sph;
	char		*key;

	radius = new_vec(1, 1, 1);
	line = get_next_line(fd, 0);
	sph = eng_new_sphere();
	while (line)
	{
		key = line;
		skip_whitespace(&key);
		value = skip_header(key);
		if (!ft_strncmp("ORIGIN", key, ft_strlen("ORIGN")))
			str_to_tuple(value, &origin, &value, 1.0);
		else if (!ft_strncmp("MATERIAL", key, ft_strlen("MATERIAL")))
			sph.base_obj.material = parse_material(fd);
		parse_radius(&radius, key, value);
		free(line);
		line = get_next_line(fd, 0);
	}
	eng_set_transform((t_obj_ptr) & sph, mtx_translate(origin.x, origin.y,
		origin.z));
	eng_set_transform((t_obj_ptr) & sph, mtx_scale(radius.x, radius.y,
		radius.z));
	eng_add_obj_to_world(world, (t_obj_ptr) & sph);
}

void	new_parse_cylinder(int fd, t_world *world)
{
}

void	new_parse_cone(int fd, t_world *world)
{
}

void	new_parse_light(int fd, t_world *world)
{
	char		*line;
	t_point		origin;
	char		*value;
	double		fov;
	double		radius;
	t_fcolor	color;
	t_light		light;
	char		*key;
	t_point		look_at;

	origin = new_point(0, 0, 0);
	radius = 1.0;
	fov = 360.0;
	look_at = new_point(0, 0, 0);
	color = new_fcolor(1.0, 1.0, 1.0, 1.0);

	line = get_next_line(fd, 0);
	while (line)
	{
		key = line;
		skip_whitespace(&key);
		value = skip_header(key);
		if (!ft_strncmp("ORIGIN", key, ft_strlen("ORIGIN")))
			str_to_tuple(value, &origin, &value, 1.0);
		else if (!ft_strncmp("FOV", key, ft_strlen("FOV")))
			fov = str_to_float(value);
		else if (!ft_strncmp("RADIUS", key, ft_strlen("RADIUS")))
			radius = str_to_float(value);
		parse_argb(key, value, &color);
		free(line);
		line = get_next_line(fd, 0);
	}
	light.origin = origin;
	light.intensity = color;
	light.radius = radius;
	if (!eq_f(fov, 360))
		light = eng_spot_light(color, origin, look_at, radius);
	else
		light = eng_point_light(color, origin);
	printf("adding light\n");
	eng_add_obj_to_world(world, (t_obj_ptr) & light);
}

void	new_parse_ambient(t_main *m_data, int fd)
{
	double		scalear;
	char		*key;
	char		*val;
	char		*line;

	line = get_next_line(fd, 0);
	m_data->engine.world.ambient42 = fcolor_black();
	while (line)
	{
		key = line;
		skip_whitespace(&key);
		val = skip_header(key);
		if (!ft_strncmp(key, "STRENGTH", ft_strlen("STRENGTH")))
			scalear = str_to_float(val);
		parse_argb(key, val, &(m_data->engine.world.ambient42));
		free(line);
		line = get_next_line(fd, 0);
	}
	m_data->engine.world.ambient42 =
		scale_fcolor(m_data->engine.world.ambient42, scalear);
}

void	parse_file(t_main *m_data, int fd, t_world *world, t_camera *camera)
{
	char			*line;

	line = get_next_line(fd, 0);
	if (ft_strncmp("TYPE", line, ft_strlen("TYPE")))
		ft_error("PARSING ERROR: first word in object file has to be 'TYPE'",
				__FILE__, __LINE__, errno);
	if (ft_strnstr(line, "CAMERA", ft_strlen(line)))
		new_parse_camera(fd, m_data, camera);
	else if (ft_strnstr(line, "PLANE", ft_strlen(line)))
		new_parse_plane(fd, world);
	else if (ft_strnstr(line, "SPHERE", ft_strlen(line)))
		new_parse_sphere(fd, world);
	else if (ft_strnstr(line, "CYLINE", ft_strlen(line)))
		new_parse_cylinder(fd, world);
	else if (ft_strnstr(line, "CONE", ft_strlen(line)))
		new_parse_cone(fd, world);
	else if (ft_strnstr(line, "LIGHT", ft_strlen(line)))
		new_parse_light(fd, world);
	else if (ft_strnstr(line, "AMBIENT", ft_strlen(line)))
		new_parse_ambient(m_data, fd);
	free(line);
}

static void	parse_line(t_main *m_data, char *line, t_world *world,
	t_camera *camera)
{
	int		fd;

	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = 0;
	fd = open(line, O_RDONLY);
	printf("%s\n", line);
	if (fd == -1)
		ft_error("Can not open file", __FILE__, __LINE__, errno);
	m_data->cleanup_data.fd2 = fd;
	parse_file(m_data, fd, world, camera);
	m_data->cleanup_data.fd2 = 0;
	close(fd);
	get_next_line(fd, true);
}

void	better_parser(t_main *m_data, char *setup_file)
{
	char	*const demo = "srcs/better_parser/setup_file_demo";
	int		fd;
	char	*line;

	setup_file = demo;
	fd = open(setup_file, O_RDONLY);
	if (fd == -1)
		ft_error("Can not open file", __FILE__, __LINE__, errno);
	m_data->cleanup_data.fd = fd;
	line = get_next_line(fd, 0);
	while (line)
	{
		parse_line(m_data, line, &m_data->engine.world, &m_data->engine.camera);
		free(line);
		line = get_next_line(fd, 0);
	}
	close(fd);
	m_data->cleanup_data.fd = 0;
	get_next_line(fd, true);
	eng_print_world(m_data->engine.world);
}
