#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>
#include <libft.h>

void	parse_line(t_main *m_data, char *line,
			size_t mem_points[PARSER_MEM_SIZE])
{
	while (ft_iswhitespace(*line))
		line++;
	if (*line == 'A')
		parse_ambient(m_data, line);
	else if (*line == 'C')
		parse_camera(m_data, line, mem_points);
	else if (*line == 'L')
		parse_light(m_data, line, mem_points);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(m_data, line, mem_points);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(m_data, line, mem_points);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cylinder(m_data, line, mem_points);
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

//TODO: validate path file type
void	parser(t_main *m_data, char *path)
{
	char	*line;
	int		fd;
	size_t	mem_points[PARSER_MEM_SIZE];

	if (!valid_file_extension(path))
		parser_error("Invalid file extension", __FILE__, __LINE__, errno);
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
	close(fd);
	m_data->cleanup_data.fd = 0;
	get_next_line(fd, true);
}
