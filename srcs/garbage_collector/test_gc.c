#include <main.h>
#include "garbage_collector.h"

int	test_gc_init(void)
{
	t_garbage_collector	*gc;
	char				*str;
	int					len;
	int					i;
	int					*a;
	char				*upper;

	gc = get_gc();
	a = malloc(sizeof(int) * 10);
	if (!a)
		return (0);
	i = -1;
	while (++i < 10)
		a[i] = i;
	len = 26;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < len)
		str[i] = 'a' + i;
	str[i] = '\0';
	//pintf("Allocated string: %s\n", str);
	gc = gc_init_garbage_collector();
	if (!gc)
		return (0);
	// printf("POST freshly inited SIZE: %zu\n", gc->size);
	gc_add_begin(gc, a);
	// printf("POST ADD SIZE: %zu\n", gc->size);
	gc_add_begin(gc, str);

	//Test mit ft_malloc (fuegt dynamisch allokierten String automatisch zu garbage collector hinzu)
	upper = ft_malloc(sizeof(char) * (len + 1));
	if (!upper)
		return (-1);
	// printf("after ,alloc head: %p\n", (gc->head));
	i = -1;
	while (++i < len)
		upper[i] = 'A' + i;
	upper[i] = '\0';
	// test = (gc->head->pointer);
	// printf("Upper via gc: %s\n", test);
	// i = -1;
	// printf("Upper via gc: %p\n", (gc->head));
	// printf("Upper via gc: %s\n", (gc->head->pointer));
	// printf("Upper direct: %s\n", upper);
	// printf("POST ADD SIZE: %zu\n", gc->size);
	// gc_free_all(gc);
	return (1);
	//TODO: ft_malloc test
}

