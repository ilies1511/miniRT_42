/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:07 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:34:08 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>


bool	test4_shadow()
{
	t_world	default_world;
	t_point	point;

	default_world = eng_default_world();
	point = new_point(-2, 2, -2);
	if (eng_is_shadowed(default_world, point, *default_world.lights))
	{
		printf("eng_is_shadow should return false\n File: %s \t Line: %d\n", __FILE__, __LINE__);
		return (false);
	}
	return (true);
}

bool	test3_shadow()
{
	t_world	default_world;
	t_point	point;

	default_world = eng_default_world();
	point = new_point(-20, 20, -20);
	if (eng_is_shadowed(default_world, point, *default_world.lights))
	{
		printf("eng_is_shadow should return false\n File: %s \t Line: %d\n", __FILE__, __LINE__);
		return (false);
	}
	return (true);
}

bool	test2_shadow()
{
	t_world	default_world;
	t_point	point;

	default_world = eng_default_world();
	point = new_point(10, -10, 10);
	if (!eng_is_shadowed(default_world, point, *default_world.lights))
	{
		printf("eng_is_shadow should return true\n File: %s \t Line: %d\n", __FILE__, __LINE__);
		return (false);
	}
	return (true);
}

bool	test_shadow()
{
	t_world	default_world;
	t_point	point;

	default_world = eng_default_world();
	point = new_point(0, 10, 0);
	if (eng_is_shadowed(default_world, point, *default_world.lights))
	{
		printf("eng_is_shadow should return false\n File: %s \t Line: %d\n", __FILE__, __LINE__);
		return (false);
	}
	return (true);
}