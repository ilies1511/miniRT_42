/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:06 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:57:53 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_material.h>
#include <ft_scene.h>

static void	ocean(t_world *world)
{
	t_light		sun_light;
	t_plane		floor;
	t_plane		water;
	t_plane		sky;

	sun_light = eng_point_light(new_fcolor(1.00001, 0.900001, 0.60000001, 1), \
		new_point(0, 100, 20));
	sun_light.radius = 20.0001;
	water = eng_new_plane();
	water.base_obj.material = eng_water();
	floor = eng_new_plane();
	eng_set_transform((t_obj_ptr) & water, \
		mtx_translate(0.00000001, 0.0000001, 0.000001));
	floor.base_obj.material = eng_sand();
	eng_set_transform((t_obj_ptr) & floor, \
		mtx_translate(0.0000001, -40.000001, 0.000001));
	sky = eng_new_plane();
	sky.base_obj.material = eng_blue_sky();
	eng_set_transform((t_obj_ptr) & sky, \
		mtx_translate(0.0000001, 100000000.00001, 0.000001));
	eng_add_obj_to_world(world, (t_obj_ptr) & sun_light);
	eng_add_obj_to_world(world, (t_obj_ptr) & water);
	eng_add_obj_to_world(world, (t_obj_ptr) & sky);
	eng_add_obj_to_world(world, (t_obj_ptr) & floor);

}

static void	init_world(t_world *world)
{
	t_sphere	sph_glass;
	t_sphere	sph;
	t_sphere	ball;

	ocean(world);
	sph_glass = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr) & sph_glass, \
		mtx_scale(1000.000001, 1000.00001, 1000.00001));
	ball = eng_new_sphere();
	ball.base_obj.material = material_silver_and_gold();
	eng_set_transform((t_obj_ptr) & ball, mtx_translate(200, 3, -570));
	eng_set_transform((t_obj_ptr) & ball, mtx_scale(2, 2, 2));
	sph = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr) & sph, mtx_translate(196, 3, -570));
	eng_set_transform((t_obj_ptr) & sph, mtx_scale(2, 2, 2));
	eng_add_obj_to_world(world, (t_obj_ptr) & floor);
}

static void	init_camera(t_main *m_data)
{
	t_camera	*camera;

	camera = &(m_data->engine.camera);
	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
	*(camera) = eng_new_camera(m_data->engine.canvas.width, \
		m_data->engine.canvas.height, M_PI / 3);
	eng_set_transform((t_obj_ptr)camera, \
	sc_transforme_view(new_point(200, 5, -600), new_point(0, 0, 0), \
		new_vec(0, 1, 0)));
}

void	demo_add_ocean(void *main_data)
{
	t_main		*m_data;
	t_world		*world;

	m_data = (t_main *)main_data;
	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
	if (m_data->ac > 2)
		store_as_plain_ppm(m_data, m_data->av[2]);
}
