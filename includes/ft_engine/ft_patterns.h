#ifndef FT_PATTERNS_H
# define FT_PATTERNS_H

#include <stdlib.h>
#include <ft_colors.h>
#include <ft_tuple.h>
#include <ft_matrix.h>
#include <ft_engine.h>

typedef struct s_obj	t_obj;


t_pattern	*pat_new_pattern(void);
t_fcolor	pat_color_at(t_obj obj, t_pattern pattern, t_point world_point);

//stripe_pattern.c
t_pattern	*pat_stripe_pattern(t_fcolor color1, t_fcolor color2);
t_fcolor	pat_stripe_at(t_pattern pat, t_point point);

//tests
bool		test_stripe_pattern(void);
bool		test_stripe_lighting(void);
bool		test_stripe_obj(void);

#endif //FT_PATTERNS_H
