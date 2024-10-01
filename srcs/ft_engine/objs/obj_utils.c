#include <ft_engine.h>
#include <main.h>

bool	eng_is_shape(t_obj_type type)
{
	return (type == OBJ_SPHERE || type == OBJ_PLANE || OBJ_CYLINDER);
}

t_obj *eng_alloc_shape(t_obj_type type)
{
	t_obj	*shape;
	char	error_type_buffer[ERROR_BUF_LEN];

	if (type == OBJ_SPHERE)
	{
		shape = ft_malloc(sizeof(t_sphere));
		*(t_sphere *)shape = eng_new_sphere();
	}
	else if (type == OBJ_PLANE)
	{
		shape = ft_malloc(sizeof(t_plane));
		*(t_plane *)shape = eng_new_plane();
	}
	else if (type == OBJ_CYLINDER)
	{
		shape = ft_malloc(sizeof(t_cylinder)); //TODO: Add malloc CHECK
		if (!shape)
			gc_free_all();
		*(t_cylinder *)shape = eng_new_cylinder();
	}
	else
	{
		ft_fprintf(2, "eng_alloc_shape: invlid shape type: %s\n",
			eng_type_to_str((t_obj_type)type, error_type_buffer));
		ft_assert(0,  __FILE__, __LINE__,
			"Assertion: eng_alloc_shape: invalid shape type");
		__builtin_unreachable();
	}
	if (!shape)
		ft_error("Error: malloc failed", __FILE__, __LINE__, 1);
	return (shape);
}

const char *eng_type_to_str(t_obj_type type, char buf[ERROR_BUF_LEN])
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
	else
	{
		ft_assert(0, __FILE__, __LINE__,
			"eng_type_to_str: unknow type");
		__builtin_unreachable();
	}
	ft_assert(ft_strlen(type_str) < ERROR_BUF_LEN, __FILE__, __LINE__,
		"eng_type_to_str: type as string is longer that ERROR_BUF_LEN");
	ft_memcpy(buf, type_str, ft_strlen(type_str));
	buf[ERROR_BUF_LEN - 1] = '\0';
	return (buf);
}
