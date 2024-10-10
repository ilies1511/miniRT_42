/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:33 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:45:45 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <main.h>

bool	eng_is_shape(t_obj_type type)
{
	return (type == OBJ_SPHERE || type == OBJ_PLANE \
		|| type == OBJ_CYLINDER || type == OBJ_CONE);
}

static t_obj_ptr	do_alloc(t_obj_ptr shape, t_obj_type type, \
	char buf[ERROR_BUF_LEN])
{
	shape = NULL;
	if (type == OBJ_SPHERE)
		shape = ft_malloc(sizeof(t_sphere));
	else if (type == OBJ_PLANE)
		shape = ft_malloc(sizeof(t_plane));
	else if (type == OBJ_CYLINDER)
		shape = ft_malloc(sizeof(t_cylinder));
	else if (type == OBJ_CONE)
		shape = ft_malloc(sizeof(t_cone));
	else
	{
		ft_fprintf(2, "invlid shape: %s\n", eng_type_to_str(type, buf));
		ft_error("eng_alloc_shape: invalid shape type", __FILE__, __LINE__, 1);
	}
	return (shape);
}

t_obj_ptr	eng_alloc_shape(t_obj_type type)
{
	t_obj_ptr	shape;
	char		buf[ERROR_BUF_LEN];

	shape = NULL;
	shape = do_alloc(shape, type, buf);
	if (!shape)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
	if (type == OBJ_SPHERE)
		*(t_sphere *)shape = eng_new_sphere();
	else if (type == OBJ_PLANE)
		*(t_plane *)shape = eng_new_plane();
	else if (type == OBJ_CYLINDER)
		*(t_cylinder *)shape = eng_new_cylinder();
	else if (type == OBJ_CONE)
		*(t_cone *)shape = eng_new_cone();
	return (shape);
}

const char	*eng_type_to_str(t_obj_type type, char buf[ERROR_BUF_LEN])
{
	const char	*type_str;

	if (type == OBJ_DEFAULT)
		type_str = "OBJ_DEFAULT";
	else if (type == OBJ_SPHERE)
		type_str = "OBJ_SPHERE";
	else if (type == OBJ_PLANE)
		type_str = "OBJ_PLANE";
	else if (type == OBJ_RAY)
		type_str = "OBJ_RAY";
	else if (type == OBJ_LIGHT)
		type_str = "OBJ_LIGHT";
	else if (type == OBJ_CAMERA)
		type_str = "OBJ_CAMERA";
	else if (type == OBJ_CONE)
		type_str = "OBJ_CONE";
	else if (type == OBJ_CYLINDER)
		type_str = "OBJ_CYLINDER";
	else
		ft_error("eng_alloc_shape: invalid shape type", __FILE__, __LINE__, 1);
	rt_assert(ft_strlen(type_str) < ERROR_BUF_LEN, __FILE__, __LINE__,
		"eng_type_to_str: type as string is longer that ERROR_BUF_LEN");
	ft_memcpy(buf, type_str, ft_strlen(type_str));
	buf[ERROR_BUF_LEN - 1] = '\0';
	return (buf);
}
