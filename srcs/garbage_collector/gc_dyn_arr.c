#include <stdint.h>
#include <stdlib.h>
#include <libft.h>
#include <main.h>

// libft funtctions but with ft_malloc instead to use the garbage collector
typedef struct s_dyn_header
{
	size_t		len;
	size_t		size;
	char		data[];
}	t_dyn_header;

void	*gc_dyn_arr_init(uint64_t data_size, size_t init_len)
{
	t_dyn_header	*arr;

	arr = (t_dyn_header *)ft_malloc(data_size * init_len + \
		sizeof(t_dyn_header));
	if (!arr)
		return (NULL);
	arr->len = init_len;
	arr->size = data_size;
	ft_bzero(arr + 1, data_size * init_len);
	return (arr + 1);
}

// double the array size
// basically realloc with calloc
// return 0 on sucess, errno for malloc error
int	gc_dyn_arr_resize(void **arr)
{
	size_t			len;
	size_t			new_len;
	size_t			data_size;
	t_dyn_header	*new;

	len = dyn_arr_get_len(*arr);
	data_size = dyn_arr_get_size(*arr);
	if (len)
		new_len = 2 * len;
	else
		new_len = 1;
	new = (t_dyn_header *)ft_malloc(data_size * new_len + sizeof(t_dyn_header));
	if (!new)
		return (ft_free(arr), errno);
	new->size = ((t_dyn_header *)*arr)[-1].size;
	new->len = new_len;
	new++;
	ft_memcpy(new, *arr, len * data_size);
	ft_bzero((uint8_t *)new + len * data_size, (new_len - len) * data_size);
	*arr = new;
	return (0);
}

// alternative to arr[index] = ... : if the arr is too small its automatically
// resized
// returns non 0 on malloc error
int	gc_dyn_arr_add_save(void **arr, void *data, size_t index)
{
	size_t	data_size;

	data_size = dyn_arr_get_size(*arr);
	if (dyn_arr_get_len(*arr) <= index)
	{
		if (gc_dyn_arr_resize(arr))
			return (errno);
	}
	ft_memmove(((uint8_t *)*arr) + data_size * index, data, data_size);
	return (0);
}
