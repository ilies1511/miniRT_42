#include <main.h>
#include "garbage_collector.h"

int	test_gc_init(void)
{
	t_garbage_collector	*gc;
	char				*str;
	int					len;
	int					i;
	int					*a;

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
	printf("Allocated string: %s\n", str);
	gc = gc_init_garbage_collector();
	if (!gc)
		return (0);
	printf("POST freshly inited SIZE: %zu\n", gc->size);
	gc_add_begin(gc, str);
	printf("POST ADD SIZE: %zu\n", gc->size);
	gc_add_begin(gc, a);
	printf("POST ADD SIZE: %zu\n", gc->size);
	gc_free_all(gc);
	return (1);
	//TODO: ft_malloc test
}

