/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:25 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:33:27 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PATTERNS_H
# define FT_PATTERNS_H

# include <stdlib.h>
# include <ft_colors.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_engine.h>

typedef struct s_obj	t_obj;

t_pattern	*pat_new_pattern(void);
t_fcolor	pat_color_at(t_obj obj, t_pattern pattern, t_point world_point);

//stripe_pattern.c
t_pattern	*pat_stripe_pattern(t_fcolor color1, t_fcolor color2);
t_fcolor	pat_stripe_at(t_pattern pat, t_point point);

//checkers_pattern.c
t_pattern	*pat_checker2d_pattern(t_fcolor color1, t_fcolor color2);
t_fcolor	pat_checker2d_at(t_pattern pat, t_point point);
t_pattern	*pat_checker3d_pattern(t_fcolor color1, t_fcolor color2);
t_fcolor	pat_checker3d_at(t_pattern pat, t_point point);

//square_pattern.c
t_pattern	*pat_square3d_pattern(t_fcolor color1, t_fcolor color2);
t_fcolor	pat_square3d_at(t_pattern pat, t_point point);

/*todo: if we want we can add more patterns
 *simple example:
	* ring pattern
	* gradiant pattern
 * more complex:
	* jutter pattern (perlin or simplex noise)
*/
//tests
bool		test_stripe_pattern(void);
bool		test_stripe_lighting(void);
bool		test_stripe_obj(void);
bool		test_checkers_pattern(void);

#endif //FT_PATTERNS_H
