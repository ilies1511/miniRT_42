/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:52 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:08:55 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// has to be called exactly onece with a pointer that is != NULL at the
// program entry
// after that this will return that pointer
t_main	*get_m_data(void)
{
	static t_main	m_data = {0};

	return (&m_data);
}

void	update_width_height(t_main *m_data)
{
	m_data->engine.canvas.width = m_data->cleanup_data.mlx_img->width;
	m_data->engine.canvas.height = m_data->cleanup_data.mlx_img->height;
	m_data->engine.camera.width = m_data->cleanup_data.mlx_img->width;
	m_data->engine.camera.height = m_data->cleanup_data.mlx_img->height;
}

void	main_loop(void *main_data)
{
	t_main	*m_data;

	m_data = (t_main *)main_data;
	update_width_height(m_data);
	eng_render(m_data->engine.camera, m_data->engine.world,
		m_data->engine.canvas);
}

void	init_hooks(t_main *m_data)
{
	mlx_close_hook(m_data->mlx, close_handler, m_data);
	mlx_key_hook(m_data->mlx, main_key_hooks, m_data);
	mlx_loop_hook(m_data->mlx, main_loop, m_data);
}

void	main_init(t_main *m_data, int ac, char *av[])
{
	if (ac == 1)
	{
		ft_fprintf(2, "Error: .rt file needed\n");
		exit(22);
	}
	ft_bzero(m_data, sizeof * m_data);
	m_data->ac = ac;
	m_data->av = av;
	m_data->camera_type = NO_CAMERA;
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
