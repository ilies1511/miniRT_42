/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:45 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:07:58 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		close_handler(m_data);
}
