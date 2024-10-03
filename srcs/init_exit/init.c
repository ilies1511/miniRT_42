#include <main.h>

// has to be called exactly onece with a pointer that is != NULL at the
// program entry
// after that this will return that pointer
t_main	*get_m_data(void)
{
	static t_main	m_data = {0};

	return (&m_data);
}

void	main_loop(void *main_data)
{
	t_main	*m_data;

	m_data = (t_main *)main_data;
	//reset_canvas(&m_data->engine.canvas);
	if (m_data->ac == 1)
		sphere_test(m_data);
	else
	{
		eng_render(m_data->engine.camera, m_data->engine.world,
			m_data->engine.canvas);
	}
}

void	init_hooks(t_main *m_data)
{
	mlx_close_hook(m_data->mlx, close_handler, m_data);
	mlx_key_hook(m_data->mlx, main_key_hooks, m_data);
	mlx_loop_hook(m_data->mlx, main_loop, m_data);
}

//can be removed later: m_data->ac
void	main_init(t_main *m_data, int ac, char *av[])
{
	ft_bzero(m_data, sizeof * m_data);
	m_data->ac = ac;
	m_data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!m_data->mlx)
	{
		ft_error("an mlx_init function call failed failed",
			__FILE__, __LINE__, 1);
	}
	m_data->cleanup_data.mlx_img = mlx_new_image(m_data->mlx, WIDTH, HEIGHT);
	if (!m_data->cleanup_data.mlx_img || mlx_image_to_window(
			m_data->mlx, m_data->cleanup_data.mlx_img, 0, 0))
	{
		ft_error("an mlx_init function call failed failed",
			__FILE__, __LINE__, 1);
	}
	eng_init_engine(m_data, ac, av);
	init_hooks(m_data);
	mlx_loop(m_data->mlx);
}
