# include <ppm_parser.h>
# include <main.h>

//opens the file, hanles open erros and write the header to the file
static t_fd	init_store_ppm(t_main *m_data, char *file_name)
{
	t_fd	fd;
	errno  = 0;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: %s\n", file_name, strerror(errno));
		ft_error(m_data, "couldn't open ppm file to store data", __FILE__,
				__LINE__, 1);
	}
	if (ft_fprintf(fd, "P3\n%d %d\n255\n", WIDTH, HEIGHT) == -1)
	{
		ft_fprintf(2, "%s: %s\n", file_name, strerror(errno));
		ft_error(m_data, "writing header to ppm file failed",
			__FILE__, __LINE__, 1);
	}
	return (fd);
}

static void	write_row(t_main *m_data, t_fd fd, size_t y)
{
	int				printf_ret;
	size_t			cur_char_in_line;
	size_t			x;
	t_uint_color	color;

	x = 0;
	while (x < WIDTH)
	{
		cur_char_in_line = 0;
		while (PPM_VAL_BLOCK_LEN + cur_char_in_line < PPM_MAX_CHARS_PER_LINE && x < WIDTH)
		{
			color.full = ((uint32_t *)m_data->img->pixels)[y * WIDTH + x];
			printf_ret = 0;
			printf_ret = ft_fprintf(fd, " %d %d %d",
				color.argb.r, color.argb.g, color.argb.b);
			if (printf_ret == -1)
				ft_error(m_data, "ft_fprintf failed: store to ppm file",
						__FILE__, __LINE__, 1);
			cur_char_in_line += printf_ret;
			x++;
		}
		if (ft_fprintf(fd, "\n") == -1)
			ft_error(m_data, "ft_fprintf failed: failed to store to ppm file",
				__FILE__, __LINE__, 1);
	}
}

void	store_as_plain_ppm(t_main *m_data, char *file_name)
{
	t_fd			fd;
	size_t			y;

	fd = init_store_ppm(m_data, file_name);
	y = 0;
	while (y < HEIGHT)
	{
		write_row(m_data, fd, y);
		y++;
	}
	if (close(fd) == -1)
		ft_error(m_data, "close: failed to close ppm file after closing it",
			__FILE__, __LINE__, 1);

}

