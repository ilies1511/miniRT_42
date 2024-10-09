#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>
#include <libft.h>

static void	parse_line2(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	if (*line == 'A')
		parse_ambient(m_data, line);
	else if (*line == 'C' && m_data->camera_type == USER_INPUT)
		parser_error("Can not have multiple cameras", __FILE__, __LINE__, 100);
	else if (*line == 'C')
	{
		m_data->camera_type = USER_INPUT;
		parse_camera(m_data, line, mem_points);
	}
	else if (*line == 'S' && line[1] == 'L')
		parse_spot_light(m_data, line, mem_points);
	else if (*line == 'L')
		parse_light(m_data, line, mem_points);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(m_data, line, mem_points);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(m_data, line, mem_points);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cylinder(m_data, line, mem_points);
	else if (line[0] == 'c' && line[1] == 'o' && line[2] != 'd')
		parse_cone(m_data, line, mem_points);
	else if (line[0] == 'c' && line[1] == 'o' && line[2] == 'd')
		parse_double_cone(m_data, line, mem_points);
}

static void	parse_line(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	while (ft_iswhitespace(*line))
		line++;
	if (!ft_strncmp("OCEAN_BALLS", line, ft_strlen("OCEAN_BALLS")))
		demo_add_ocean_balls(m_data);
	else if (!ft_strncmp("OCEAN", line, ft_strlen("OCEAN")))
		demo_add_ocean(m_data);
	else if (!ft_strncmp("ONE_PIECE", line, ft_strlen("ONE_PIECE")))
		one_piece(m_data);
	else if (!ft_strncmp("NICE", line, ft_strlen("NICE")))
		reflection_demo(m_data);
	else if (!ft_strncmp("INNER_SPHERE", line, ft_strlen("INNER_SPHERE")))
		inner_sphere_demo(m_data);
	else if (!ft_strncmp("CHECKER_REFLECTION", line, \
		ft_strlen("CHECKER_REFLECTION")))
		internal_reflection_demo(m_data);
	else
		parse_line2(m_data, line, mem_points);
}

bool	valid_file_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 3)
		return (false);
	path += len - 3;
	return (!ft_strcmp(path, ".rt"));
}

void	parser(t_main *m_data, char *path)
{
	char	*line;
	int		fd;
	size_t	mem_points[PARSER_MEM_SIZE];

	if (!valid_file_extension(path))
		parser_error("Invalid file extension", __FILE__, __LINE__, 100);
	m_data->engine.world.ambient42 = scale_fcolor(fcolor_white(), 0.2);
	ft_bzero(mem_points, sizeof mem_points);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		parser_error("Can not open file", __FILE__, __LINE__, errno);
	m_data->cleanup_data.fd = fd;
	line = get_next_line(fd, false);
	while (line)
	{
		parse_line(m_data, line, mem_points);
		free(line);
		line = get_next_line(fd, false);
	}
	if (m_data->camera_type == NO_CAMERA)
		parser_error("Needs Camera", __FILE__, __LINE__, 100);
	close(fd);
	m_data->cleanup_data.fd = 0;
	get_next_line(fd, true);
}
