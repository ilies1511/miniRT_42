#include <ft_engine.h>
#include <libft.h>
#include <main.h>
#include <ft_patterns.h>

t_pattern	*pat_new_pattern(void)
{
	t_pattern	*pattern;

	pattern = ft_malloc(sizeof(t_pattern));
	if (!pattern)
		ft_error("Malloc failed", __FILE__, __LINE__, 1);
	pattern->base_obj = eng_new_obj();
	pattern->base_obj.type = OBJ_PATTERN;
	pattern->type = PAT_DEFAULT;
	pattern->color_count = 1;
	pattern->colors = gc_dyn_arr_init(sizeof(t_fcolor), 1);
	if (!pattern->colors)
		ft_error("Error: Malloc failed", __FILE__, __LINE__, 1);
	pattern->colors[0] = fcolor_white();
	return (pattern);
}

t_fcolor	pat_color_at(t_obj obj, t_pattern pattern, t_point world_point)
{
	t_point	obj_point;
	t_point	pattern_point;

	//printf("*****************\n");
	//mtx_print(1, obj.inverse);
	//mtx_print(1, pattern.base_obj.transform);
	obj_point = mtx_mult_mt(obj.inverse, world_point);
	pattern_point = mtx_mult_mt(pattern.base_obj.inverse, obj_point);
	//print_t(1, pattern_point);
	//if (pattern.type == PAT_DEFAULT)
	//	return (pattern.colors[0]);
	//else if (pattern.type == PAT_STRIPE)
		return (pat_stripe_at(pattern, pattern_point));
	ft_assert(0, __FILE__, __LINE__, "pat_color_at: invalid pattern type");
	__builtin_unreachable();
}
