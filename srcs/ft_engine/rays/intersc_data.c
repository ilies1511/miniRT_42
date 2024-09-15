#include <ft_engine.h>
#include <libft.h>
#include <main.h>

static bool	swap_intersc(void *a, void *b)
{
	return (((t_intersc *)a)->t > ((t_intersc *)b)->t);
}

/*
 * t_intersc	*data:
	* output for INTERSC_GET
	* input for INTERSC_PUSH
	* for others: irrelevant
 *	size_t	*i:
	* intput INTERSC_GET: used as the index for the returned element
	* output INTERSC_COUNT: used used to return the count
	* for others: irrelevant
*/
static void	intersections(t_intersc_op op, size_t *i, t_intersc *data)
{
	static t_intersc	*interscs = NULL;
	static	size_t		count = 0;

	if (!interscs)
		interscs = dyn_arr_init(sizeof(t_intersc), 0);
	if (!interscs)
		ft_error("intersc: malloc error", __FILE__, __LINE__, 1);
	if (op == INTERSC_GET)
	{
		ft_assert(*i < count, __FILE__, __LINE__, "Error: intersc: \
			INTERSC_GET: invalid index i");
		*data = interscs[*i];
	}
	else if (op == INTERSC_COUNT)
		*i = count;
	else if (op == INTERSC_PUSH)
		dyn_arr_add_save((void **)(&interscs), data, count++);
	else if (op == INTERSC_SORT)
		ft_sort(interscs, sizeof(t_intersc), count, swap_intersc);
	else if (op == INTERSC_FREE)
	{
		dyn_arr_free((void **)(&interscs));
		count = 0;
	}
	else
		ft_assert(0, __FILE__, __LINE__, "intersc: invalid op code");
	if (!interscs && op != INTERSC_FREE)
		ft_error("intersc: malloc error", __FILE__, __LINE__, 1);
}

void	eng_free_intersc(void)
{
	intersections(INTERSC_FREE, NULL, NULL);
}

t_intersc	eng_get_intersc(size_t i)
{
	t_intersc	intersc;

	intersections(INTERSC_GET, &i, &intersc);
	return (intersc);
}

void	eng_sort_intersc(void)
{
	intersections(INTERSC_SORT, NULL, NULL);
}

size_t	eng_count_intersc(void)
{
	size_t	count;

	intersections(INTERSC_COUNT, &count, NULL);
	return (count);
}

void	eng_new_intersc(t_obj *obj, float t)
{
	t_intersc	intersc;

	intersc.t = t;
	intersc.type = obj->type;
	intersc.obj = obj;
	intersections(INTERSC_PUSH, NULL, &intersc);
}
