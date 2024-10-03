#ifndef FT_REFRACTION_H
# define FT_REFRACTION_H

# include <stdbool.h>
# include <ft_tuple.h>
# include <ft_colors.h>
# include <ft_engine.h>

t_fcolor	refracted_color(t_world world, t_computation comp, size_t remaining);
bool	test_prepare_comp_n1_n2(void);
bool	test_prepare_comp_underpoint(void);
bool	test_refracted_color(void);
bool	test_refracted_color_total_reflect(void);
bool	test_shade_hit_with_transparent_material(void);
#endif //FT_REFRACTION_H
