#include <ft_engine.h>
#include <libft.h>
#include <ft_floats.h>
#include <ft_reflection.h>
#include <ft_patterns.h>

t_point	mult_p_scalar(t_point point, double scale)
{
	t_point	new;

	new.x = point.x * scale;
	new.y = point.y * scale;
	new.z = point.z * scale;
	return (new);
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
	if (dot_prod(comp.normal_v, comp.eye_v) < 0)
	{
		comp.inside = true;
		comp.normal_v = negate_v(comp.normal_v);
	}
	else
		comp.inside = false;
	comp.over_point = add_t(comp.point, mult_v(comp.normal_v, (EPSILON)));
	comp.under_point = sub_t(comp.point, mult_v(comp.normal_v, (EPSILON)));
	comp.reflection = ref_reflect(ray.direct, comp.normal_v);
	if (comp.obj->material.pattern)
		comp.color_at = pat_color_at(*(comp.obj),
				*(comp.obj->material.pattern), comp.over_point);
	else
		comp.color_at = (comp.obj->material.fcolor);

	t_list		*containers;
	size_t		i;
	t_intersc	intersc;

	containers = NULL;
	i = 0;
	while (i < interscs.count)
	{
		intersc = interscs.arr[i];
		if (eq_f(intersc.t, hit.t) && intersc.obj == hit.obj)
		{
			if (!containers)
				comp.n1 = 1.0;
			else
				comp.n1 = ((t_obj_ptr)(ft_lstlast(containers)->content))->material.refractive_index;
		}
		t_list *last = NULL;
		t_list	*cur = containers;
		while (cur && cur->content != intersc.obj)
		{
			last = cur;
			cur = cur->next;
		}
		if (cur)
		{
			while (cur)
			{
				if (cur->content == intersc.obj)
				{
					if (last)
					{
						last->next = cur->next;
						free(cur);
						cur = last;
					}
					else
					{
						containers = cur->next;
						last = cur;
						cur = cur->next;
						free(last);
					}
					if (!cur)
						break ;
				}
				last = cur;
				cur = cur->next;
			}
		}
		else
			ft_lstadd_back(&containers, ft_lstnew(intersc.obj));
		if (eq_f(intersc.t, hit.t) && intersc.obj == hit.obj)
		{
			if (!containers)
				comp.n2 = 1.0;
			else
				comp.n2 = ((t_obj_ptr)(ft_lstlast(containers)->content))->material.refractive_index;
		}
		i++;
	}
	ft_lstclear(&containers, ft_lst_dummy_del);

	return (comp);
}
