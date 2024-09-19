#include <main.h>


void	main_cleanup(t_main *m_data, uint8_t exit_stat)
{
	eng_free_canvas(m_data->mlx, &m_data->canvas);
	mlx_close_window(m_data->mlx);
	exit(exit_stat);
}



void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	t_main	*m_data;

	m_data = get_m_data();
	ft_fprintf(2, "error in %s in line %d: %s\n", file, line, msg);
	main_cleanup(m_data, exit_stat);
}


