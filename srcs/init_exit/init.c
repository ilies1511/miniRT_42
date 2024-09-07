#include <main.h>

void	main_loop(void *main_data)
{
	t_main	*m_data;

	m_data = (t_main *)main_data;
	reset_img(m_data);
	draw_projectile(m_data);
}

void	init_hooks(t_main *m_data)
{
	mlx_close_hook(m_data->mlx, close_handler, m_data);
	mlx_key_hook(m_data->mlx, main_key_hooks, m_data);
	mlx_loop_hook(m_data->mlx, main_loop, m_data);
}

void	main_init(t_main *m_data)
{
	ft_bzero(m_data, sizeof *m_data);
	m_data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	m_data->img = mlx_new_image(m_data->mlx, WIDTH, HEIGHT);
	if (!m_data->mlx || !m_data->img
			|| mlx_image_to_window(m_data->mlx, m_data->img, 0, 0))
	{
		ft_error(m_data, "an mlx_init function call failed failed",
			__FILE__, __LINE__, 1);
	}
	reset_img(m_data);
	init_hooks(m_data);
	mlx_loop(m_data->mlx);
}

