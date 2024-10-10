/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:57 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:26:43 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <libft.h>

static inline double	kahan_sum_inline(double *nbs, size_t count)
{
	size_t	i;
	double	sum;
	double	next_add;
	double	compensation;
	double	total;

	i = 0;
	sum = 0.0;
	compensation = 0.0;
	total = 0.0;
	while (i < count)
	{
		next_add = nbs[i] - compensation;
		total = sum + next_add;
		compensation = (total - sum) - next_add;
		sum = total;
		i++;
	}
	return (sum);
}

static inline t_tuple	mtx_mult_mt_inline(t_matrix m, t_tuple tup)
{
	t_tuple	res;
	double	tmp[4] __attribute((aligned(16)));
	uint8_t	j;
	uint8_t	i;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp[j] = m.m[i][j] * tup.arr[j];
			j++;
		}
		res.arr[i] = kahan_sum_inline(tmp, 4);
		i++;
	}
	return (res);
}

// proof in sphere_proof.md
// simplified with the assumtion of unit spheres in object space
static inline void	eng_intersc_ray_sphere(t_intersc_arr *interscs, t_ray ray,
		t_sphere *sph)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;

	ray.origin.w = 0;
	a = ray.direct.x * ray.direct.x + ray.direct.y * ray.direct.y
		+ ray.direct.z * ray.direct.z;
	b = 2 * (ray.origin.x * ray.direct.x + ray.origin.y * ray.direct.y \
		+ ray.origin.z * ray.direct.z);
	c = (ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y \
		+ ray.origin.z * ray.origin.z) - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	sqrt_discriminant = sqrt(discriminant);
	eng_add_intersc(interscs, (t_obj_ptr)sph, \
		(-b + sqrt_discriminant) / (2 * a));
	eng_add_intersc(interscs, (t_obj_ptr)sph, \
		(-b - sqrt_discriminant) / (2 * a));
}

// assumes the plane to be the xz plane (normal == 0, 1, 0) at y = 0
static inline void	eng_intersc_ray_plane(t_intersc_arr *interscs, t_ray ray,
	t_plane *plane)
{
	double	t;

	if (fabsl(ray.direct.y) < (EPSILON))
		return ;
	t = -ray.origin.y / ray.direct.y;
	eng_add_intersc(interscs, (t_obj_ptr)plane, t);
}

void	eng_ray_intersc_world(t_ray ray, t_world world, t_intersc_arr *interscs)
{
	int		i;
	t_point	origin;
	t_vec	direct;

	origin = ray.origin;
	direct = ray.direct;
	i = -1;
	while (++i < (int)world.obj_count)
	{
		ray.origin = mtx_mult_mt_inline(world.objs[i]->inverse, origin);
		ray.direct = mtx_mult_mt_inline(world.objs[i]->inverse, direct);
		if (world.objs[i]->type == OBJ_SPHERE)
			eng_intersc_ray_sphere(interscs, ray, (t_sphere *)world.objs[i]);
		else if (world.objs[i]->type == OBJ_PLANE)
			eng_intersc_ray_plane(interscs, ray, (t_plane *)world.objs[i]);
		else if (world.objs[i]->type == OBJ_CYLINDER)
			eng_intersc_ray_cylinder(interscs, ray, \
				(t_cylinder *)world.objs[i]);
		else if (world.objs[i]->type == OBJ_CONE)
			eng_intersc_ray_cone(interscs, ray, (t_cone *)world.objs[i]);
		else
			rt_assert(0, __FILE__, __LINE__, \
				"eng_intersc_ray: invalid obj type");
	}
	eng_sort_intersc(interscs);
}

/*
 * Changed since inlining the math OPs gives major speed ups
 * not possible with original vesion and 42 norm duo too many functions per file

 * original Version:
void	eng_intersc_ray(t_intersc_arr *interscs, t_ray ray, t_obj_ptr obj)
{
	ray.origin = mtx_mult_mt_inline(obj->inverse, ray.origin);
	ray.direct = mtx_mult_mt_inline(obj->inverse, ray.direct);
	if (obj->type == OBJ_SPHERE)
		eng_intersc_ray_sphere(interscs, ray, (t_sphere *)obj);
	else if (obj->type == OBJ_PLANE)
		eng_intersc_ray_plane(interscs, ray, (t_plane *)obj);
	else if (obj->type == OBJ_CYLINDER)
		eng_intersc_ray_cylinder(interscs, ray, (t_cylinder *)obj);
	else if (obj->type == OBJ_CONE)
		eng_intersc_ray_cone(interscs, ray, (t_cone *)obj);
	else
		rt_assert(0, __FILE__, __LINE__, "eng_intersc_ray: invalid obj type");
}

void	eng_ray_intersc_world(t_ray ray, t_world world, t_intersc_arr *interscs)
{
	size_t	i;

	i = 0;
	while (i < world.obj_count)
	{
		eng_intersc_ray(interscs, ray, world.objs[i]);
		i++;
	}
	eng_sort_intersc(interscs);
}
*/
