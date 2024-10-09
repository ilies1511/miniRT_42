/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:49 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:50 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>
#include <libft.h>
#include <parser_42.h>

t_world	eng_new_world(void)
{
	t_world	world;

	ft_bzero(&world, sizeof world);
	world.lights = gc_dyn_arr_init(sizeof(t_light), 0);
	world.light_count = 0;
	world.objs = gc_dyn_arr_init(sizeof(t_obj_ptr), 0);
	world.obj_count = 0;
	world.ambient42 = fcolor_black();
	return (world);
}

//better_parser(m_data, av[1]);
void	eng_init_engine(t_main *m_data, int ac, char *av[])
{
	t_engine	*engine;

	engine = &m_data->engine;
	engine->world = eng_new_world();
	engine->canvas = eng_new_canvas(m_data, WIDTH, HEIGHT);
	if (ac > 1)
	{
		parser(m_data, av[1]);
	}
}