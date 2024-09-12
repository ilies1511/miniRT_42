#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

bool	test_mtx_eq(void)
{
	t_matrix	last;
	t_matrix	cur;
	bool		ret;

	last = mtx_get_rdm_m(0);
	ret = true;
	for (int i = 0; i < 10000; i++)
	{
		cur = mtx_get_rdm_m(0);
		if (mtx_eq(last, cur))
		{
			ft_fprintf(2, "random matrixes seem to be the same, likely mtx_eq()\
				error. Tho it is possible that these two are the same:\n");
			mtx_print(2, last);
			mtx_print(2, cur);
			ft_fprintf(2, "if the above 2 are the same rerun the tests since\
				this was counted as a fail");
			ret = false;
		}
		last = cur;
		if (!mtx_eq(last, cur))
		{
			ft_fprintf(2, "mtx_eq() said identical matrixes are not the same:\n");
			mtx_print(2, last);
			mtx_print(2, cur);
			ret = false;
		}
	}
	return (ret);
}

