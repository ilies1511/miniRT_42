#include <ft_engine.h>
#include <libft.h>

void	eng_free_intersc_arr(t_intersc_arr *interscs)
{
	dyn_arr_free((void **)(&interscs->arr));
	interscs->count = 0;
}
