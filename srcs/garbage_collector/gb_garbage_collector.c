#include <garbage_collector.h>

void	gc_print_linked_list(t_garbage_collector *gc)
{
	// int			i;
	// t_gc_node	*current;

	if (!gc)
		return ;
	printf("Len of Linked List: %zu\n", gc->size);
	return ;
}

void	gc_free_all(t_garbage_collector *gc)
{
	int			len;
	int			i;
	t_gc_node	*temp;
	t_gc_node	*current;

	if (!gc)
		return ;
	current = gc->head;
	len = gc->size;
	i = -1;
	while (++i < len && current)
	{
		temp = current->next;
		free(current->pointer);
		free(current);
		current = temp;
	}
	// #ifndef FSAN
	// #endif
	free(gc);
	gc = NULL;
}

t_gc_node	*gc_create_node(void *pointer2mem)
{
	t_gc_node	*new_node;

	new_node = (t_gc_node *)malloc(sizeof(t_gc_node) * 1);
	if (!new_node)
		return (NULL);
	new_node->pointer = pointer2mem;
	return (new_node);
}

/*
	Function that will be used after Malloc
*/
void	gc_add_begin(t_garbage_collector *gc, void *pointer)
{
	t_gc_node	*new_node;

	if (!pointer)
		return ;
	new_node = gc_create_node(pointer);
	if (!new_node)
	{
		gc_free_all(gc); //TODO: Clean EXIT ?

	}
	if (gc->head == NULL)
	{
		new_node->next = NULL;
		gc->head = new_node;
		gc->tail = new_node;
	}
	else
	{
		new_node->next = (gc->head);
		gc->head = new_node;
	}
	gc->size++;
}

//TODO:
// void	*ft_malloc(size_t size)
// {
// 	void				*ptr;
// 	t_garbage_collector	*gc;

// 	ptr = malloc(size);
// 	gc = get_gc(); //TODO: (16.09.24) get_data, that will give us data thanks to static gc (struct)
// 	gc_add_begin(gc, ptr);
// 	return (ptr);
// }

t_garbage_collector	*gc_init_garbage_collector(void)
{
	t_garbage_collector	*gc;

	gc = (t_garbage_collector *)malloc(sizeof(t_garbage_collector) * 1);
	if (!gc)
		return (NULL);
	gc->head = NULL;
	gc->tail = NULL;
	gc->size = 0;
	return (gc);
}

