/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:30 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:33:35 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REFLECTION_H
# define FT_REFLECTION_H

# include <stdbool.h>
# include <ft_tuple.h>
# include <ft_colors.h>
# include <ft_engine.h>

t_vec		ref_reflect(t_vec vec, t_vec surface_normal);
t_fcolor	ref_reflected_color(t_world world, t_computation comp,
				size_t remaining_reflects);

bool		test_eng_reflect(void);
bool		test_ref_reflect_color_none(void);
bool		test_ref_reflect_color(void);
bool		test_ref_with_shade_hit(void);
bool		test_ref_infinite_recursion(void);
#endif //FT_REFLECTION_H
