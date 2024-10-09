/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:38 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:31:39 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

size_t	parser_hash_point(t_point point)
{
	size_t	hash;
	t_vec	vec;

	vec = sub_t(point, new_point(0, 0, 0));
	vec = mult_v(vec, PARSER_HASH_SCALAR);
	hash = ((size_t)(PARSER_HASH_PRIME * PARSER_HASH_PRIME * vec.x
				+ PARSER_HASH_PRIME * vec.y
				+ vec. x)) % PARSER_MEM_SIZE;
	return (hash);
}

size_t	parser_get_mem_count(size_t mem[PARSER_MEM_SIZE], t_point point)
{
	size_t	hash;

	hash = parser_hash_point(point);
	return (mem[hash]);
}

void	parser_inc_mem(size_t mem[PARSER_MEM_SIZE], t_point point)
{
	size_t	hash;

	hash = parser_hash_point(point);
	mem[hash]++;
}

t_point	handle_point_collision(size_t mem_points[PARSER_MEM_SIZE],
			t_point point, double obj_modulo_prime)
{
	double	collision_offset;
	t_tuple	quick_fix_offset;

	quick_fix_offset = new_vec(obj_modulo_prime, obj_modulo_prime,
			obj_modulo_prime);
	quick_fix_offset = mult_v(quick_fix_offset, -EPSILON);
	return (add_t(point, quick_fix_offset));
	collision_offset = obj_modulo_prime
		* parser_get_mem_count(mem_points, point);
	parser_inc_mem(mem_points, point);
	point = add_t(point,
			new_vec(collision_offset, collision_offset, collision_offset));
	return (point);
}
