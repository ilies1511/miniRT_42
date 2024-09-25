#include <garbage_collector.h>

// TODO: gc_overwrite();

t_garbage_collector	*get_gc(void)
{
	static t_garbage_collector	gc = {0};

	// if (flag)
	// 	;// gc_overwrite();
	return (&gc);
}

void	gc_print_linked_list(t_garbage_collector *gc)
{
	// int			i;
	// t_gc_node	*current;

	if (!gc)
		return ;
	printf("Len of Linked List: %zu\n", gc->size);
	return ;
}

//TODO:
void	*ft_malloc(size_t len)
{
	void				*ptr;

	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	// printf("in ft_mall: %p\n", gc);
	gc_add_begin(ptr);
	// printf("end ft_mall: %p\n", gc->head);
	return (ptr);
}
