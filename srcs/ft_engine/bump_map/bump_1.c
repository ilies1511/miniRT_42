#include <ft_bump_map.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>

// t_pattern	*pat_checker2d_pattern(t_fcolor color1, t_fcolor color2)
// {
// 	t_pattern	*pattern;

// 	pattern = pat_new_pattern();
// 	pattern->type = PAT_CHECKER_2D;
// 	gc_dyn_arr_add_save((void **)&pattern->colors, &color1, 0);
// 	gc_dyn_arr_add_save((void **)&pattern->colors, &color2, 1);
// 	pattern->color_count = 2;
// 	return (pattern);
// }

// t_fcolor	pat_checker2d_at(t_pattern pat, t_point point)
// {
// 	int	ix;
// 	int	iz;

// 	ix = fabs(fmod(floor(point.x), 2));
// 	iz = fabs(fmod(floor(point.z), 2));
// 	return (pat.colors[(ix + iz) % 2]);
// }

// t_pattern	*pat_checker3d_pattern(t_fcolor color1, t_fcolor color2)
// {
// 	t_pattern	*pattern;

// 	pattern = pat_new_pattern();
// 	pattern->type = PAT_CHECKER_3D;
// 	gc_dyn_arr_add_save((void **)&pattern->colors, &color1, 0);
// 	gc_dyn_arr_add_save((void **)&pattern->colors, &color2, 1);
// 	pattern->color_count = 2;
// 	return (pattern);
// }

// t_fcolor	pat_checker3d_at(t_pattern pat, t_point point)
// {
// 	int	ix;
// 	int	iy;
// 	int	iz;
// 	int	ixz;

// 	ix = fabs(fmod(floor(point.x), 2));
// 	iy = fabs(fmod(floor(point.y), 2));
// 	iz = fabs(fmod(floor(point.z), 2));
// 	ixz = (ix + iz) % 2;
// 	return (pat.colors[(ixz + iy) % 2]);
// }
