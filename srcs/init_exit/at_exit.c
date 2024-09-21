#include <main.h>
void	main_cleanup(t_main *m_data, uint8_t exit_stat)
{
	cleanup_engine(&m_data->engine);
	mlx_delete_image(m_data->mlx, m_data->cleanup_data.mlx_img);
	mlx_close_window(m_data->mlx);
	gc_free_all(get_gc());
	bzero(m_data, sizeof *m_data);
	//system("leaks miniRT");
	exit(exit_stat);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	t_main	*m_data;

	m_data = get_m_data();
	ft_fprintf(2, "error in %s in line %d: %s\n", file, line, msg);
	main_cleanup(m_data, exit_stat);
}


