/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:00 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 14:53:14 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <libft.h>

static bool	swap_intersc(void *a, void *b)
{
	return (((t_intersc *)a)->t > ((t_intersc *)b)->t);
}

void	eng_sort_intersc(t_intersc_arr *interscs)
{
	ft_sort(interscs->arr, sizeof(t_intersc), interscs->count, swap_intersc);
}

t_intersc	eng_add_intersc(t_intersc_arr *interscs, t_obj_ptr obj, double t)
{
	t_intersc		intersc;

	intersc.t = t;
	intersc.obj = obj;
	if (!interscs->arr)
		*interscs = eng_new_intersc_arr();
	dyn_arr_add_save((void **)(&interscs->arr), &intersc, interscs->count++);
	return (intersc);
}

t_intersc_arr	eng_new_intersc_arr(void)
{
	t_intersc_arr	arr;

	arr.arr = dyn_arr_init(sizeof(t_intersc), 0);
	if (!arr.arr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	arr.count = 0;
	return (arr);
}
