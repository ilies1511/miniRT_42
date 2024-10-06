#include <main.h>

// #ifdef NDBUG


// #else

// #endif

// zero out static vars to detect leaks with fsan or valgrind
// leaks detected by valgrind from mlx_init():
// ==40446==    still reachable: 309,526 bytes in 3,127 blocks
noreturn void	main_cleanup(t_main *m_data, uint8_t exit_stat)
{
	if (m_data->mlx)
	{
		if (m_data->cleanup_data.mlx_img)
			mlx_delete_image(m_data->mlx, m_data->cleanup_data.mlx_img);
		mlx_close_window(m_data->mlx);
		mlx_terminate(m_data->mlx);
	}
	gc_free_all();
	get_next_line(-1, true);
	if (m_data->cleanup_data.fd)
		close(m_data->cleanup_data.fd);
	ft_bzero(m_data, sizeof * m_data);
	ft_bzero(get_gc(), sizeof(t_garbage_collector));
	exit(exit_stat);
}
//system("leaks miniRT");

noreturn void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	t_main	*m_data;

	m_data = get_m_data();
	ft_fprintf(2, "error in %s in line %d: %s\n", file, line, msg);
	main_cleanup(m_data, exit_stat);
}
