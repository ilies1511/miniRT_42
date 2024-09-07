#include <main.h>

void	close_handler(void *main_data)
{
	t_main	*m_data;

	m_data = (t_main *)main_data;
	main_cleanup(m_data, 0);
}

void	main_key_hooks(mlx_key_data_t keydata, void *main_data)
{
	t_main	*m_data;

	m_data = (t_main *)main_data;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_handler(m_data);
}
