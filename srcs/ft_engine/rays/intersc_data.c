#include <ft_engine.h>
#include <libft.h>
#include <main.h>

t_intersc_arr	*eng_get_intersc(void)
{
	static t_intersc_arr	interscs = {0};

	if (!interscs.arr)
		interscs.arr = dyn_arr_init(sizeof(t_intersc), 0);
	if (!interscs.arr)
		ft_error("intersc: malloc error", __FILE__, __LINE__, 1);
	return (&interscs);
}

void	eng_free_intersc(void)
{
	t_intersc_arr	*interscs;

	interscs = eng_get_intersc();
	dyn_arr_free((void **)(&interscs->arr));
	interscs->count = 0;
}

static bool	swap_intersc(void *a, void *b)
{
	return (((t_intersc *)a)->t > ((t_intersc *)b)->t);
}

void	eng_sort_intersc(void)
{
	t_intersc_arr	*interscs;

	interscs = eng_get_intersc();
	ft_sort(interscs->arr, sizeof(t_intersc), interscs->count, swap_intersc);
}

void	eng_new_intersc(t_obj *obj, float t)
{
	t_intersc		intersc;
	t_intersc_arr	*interscs;

	interscs = eng_get_intersc();
	intersc.t = t;
	intersc.type = obj->type;
	intersc.obj = obj;
	dyn_arr_add_save((void **)(&interscs->arr), &intersc, interscs->count++);
}
