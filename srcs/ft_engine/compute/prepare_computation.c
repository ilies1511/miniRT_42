/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:37:03 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:37:05 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>
#include <ft_reflection.h>
#include <ft_patterns.h>

static t_list	*del_node(t_list **list, t_list **cur, t_list *last)
{
	if (last)
	{
		last->next = (*cur)->next;
		free(*cur);
		*cur = last;
	}
	else
	{
		*list = (*cur)->next;
		last = *cur;
		*cur = (*cur)->next;
		free(last);
	}
	return (*cur);
}

static t_list	*find_obj(t_list *list, t_list **cur, t_list **last,
		t_obj_ptr obj)
{
	*last = NULL;
	*cur = list;
	while (*cur && (*cur)->content != obj)
	{
		*last = *cur;
		*cur = (*cur)->next;
	}
	return (*cur);
}

static double	get_n(t_list *list)
{
	if (!list)
		return (1.0);
	return (((t_obj_ptr)(ft_lstlast(list)->content))
			->material.refractive_index);
}

static void	fill_n1_n2(t_computation *comp, t_intersc *interscs,
	size_t intersc_count, t_intersc hit)
{
	t_list		*list;
	t_intersc	intersc;
	t_list		*last;
	t_list		*cur;

	list = NULL;
	while (intersc_count--)
	{
		intersc = *(interscs++);
		if (eq_f(intersc.t, hit.t) && intersc.obj == hit.obj)
			comp->n1 = get_n(list);
		if (!find_obj(list, &cur, &last, intersc.obj))
			ft_lstadd_back(&list, ft_lstnew(intersc.obj));
		while (cur)
		{
			if (cur->content == intersc.obj && !del_node(&list, &cur, last))
				break ;
			last = cur;
			cur = cur->next;
		}
		if (eq_f(intersc.t, hit.t) && intersc.obj == hit.obj)
			comp->n2 = get_n(list);
	}
	ft_lstclear(&list, ft_lst_dummy_del);
}

t_computation	eng_prepare_computation(t_intersc hit, t_ray ray,
		t_intersc_arr interscs)
{
	t_computation	comp;

	ft_bzero(&comp, sizeof comp);
	comp.t = hit.t;
	comp.obj = hit.obj;
	comp.color_at = (hit.obj->material.fcolor);
	comp.point = eng_ray_pos(ray, comp.t);
	comp.eye_v = negate_v(ray.direct);
	comp.normal_v = eng_normal_at(comp.obj, comp.point);
	comp.inside = false;
	if (dot_prod(comp.normal_v, comp.eye_v) < 0)
	{
		comp.inside = true;
		comp.normal_v = negate_v(comp.normal_v);
	}
	comp.over_point = add_t(comp.point, mult_v(comp.normal_v, (EPSILON)));
	comp.under_point = sub_t(comp.point, mult_v(comp.normal_v, (EPSILON)));
	comp.reflection = ref_reflect(ray.direct, comp.normal_v);
	if (comp.obj->material.pattern)
		comp.color_at = pat_color_at(*(comp.obj),
				*(comp.obj->material.pattern), comp.over_point);
	else
		comp.color_at = (comp.obj->material.fcolor);
	fill_n1_n2(&comp, interscs.arr, interscs.count, hit);
	return (comp);
}
