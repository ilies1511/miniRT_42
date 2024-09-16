#include <garbage_collector.h>

// TODO: gc_overwrite();

t_garbage_collector	*get_gc()
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
