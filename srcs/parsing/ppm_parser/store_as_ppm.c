/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_as_ppm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:14 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:31:15 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ppm_parser.h>
#include <main.h>

// void create_filename(char *filename, size_t size) {
// 	// Hole das aktuelle Datum und die Uhrzeit
// 	time_t rawtime;
// 	struct tm *timeinfo;
// 	char buffer[80];
// 	time(&rawtime);
// 	timeinfo = localtime(&rawtime);
// 	// Formatierung des Zeitstempels: z.B. "2024-09-26_15-30-45"
// 	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);
// 	// Erstelle den Dateinamen mit dem Zeitstempel
// 	snprintf(filename, size, "screenshot_%s.ppm", buffer);
// }

//opens the file, hanles open erros and write the header to the file
static t_fd	init_store_ppm(t_canvas *canvas, char *file_name)
{
	t_fd	fd;

	errno = 0;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: %s\n", file_name, strerror(errno));
		ft_error("couldn't open ppm file to store data", __FILE__,
			__LINE__, 1);
	}
	if (ft_fprintf(fd, "P3\n%d %d\n255\n", canvas->width, canvas->height) == -1)
	{
		ft_fprintf(2, "%s: %s\n", file_name, strerror(errno));
		ft_error("writing header to ppm file failed",
			__FILE__, __LINE__, 1);
	}
	return (fd);
}

static void	write_row(t_main *m_data, t_fd fd, size_t offset)
{
	int				printf_ret;
	size_t			cur_char_in_line;
	size_t			x;
	t_uintcolor		color;

	x = 0;
	while (x < m_data->engine.canvas.width)
	{
		cur_char_in_line = 0;
		while (PPM_VAL_BLOCK_LEN + cur_char_in_line < PPM_MAX_CHARS_PER_LINE
			&& x < m_data->engine.canvas.width)
		{
			color = m_data->engine.canvas.pixels[offset + x++];
			printf_ret = 0;
			printf_ret = ft_fprintf(fd, " %d %d %d",
					color.argb.r, color.argb.g, color.argb.b);
			if (printf_ret == -1)
				ft_error("ft_fprintf failed: store to ppm file",
					__FILE__, __LINE__, 1);
			cur_char_in_line += printf_ret;
		}
		if (ft_fprintf(fd, "\n") == -1)
			ft_error("ft_fprintf failed: failed to store to ppm file",
				__FILE__, __LINE__, 1);
	}
}

void	store_as_plain_ppm(t_main *m_data, char *file_name)
{
	t_fd			fd;
	size_t			y;

	fd = init_store_ppm(&m_data->engine.canvas, file_name);
	y = 0;
	while (y < m_data->engine.canvas.height)
	{
		write_row(m_data, fd, y * m_data->engine.canvas.width);
		y++;
	}
	if (close(fd) == -1)
		ft_error("close: failed to close ppm file after closing it",
			__FILE__, __LINE__, 1);
}
