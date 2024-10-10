// #include <main.h>
// #include "garbage_collector.h"

// int	test_gc_init(void)
// {
// 	char				*chars_test;
// 	int					len;
// 	int					i;
// 	char				cur_char;
// 	int					*digits_test;
// 	char				*upper;

// 	/* called from main now
// 	//gc = gc_init_garbage_collector();
// 	*/

// 	digits_test = malloc(sizeof(int) * 10);
// 	if (!digits_test)
// 		rt_assert(0, __FILE__, __LINE__, "malloc fail in test");
// 	i = -1;
// 	while (++i < 10)
// 		digits_test[i] = i;
// 	gc_add_begin(digits_test);

// 	len = 'z' - 'a' + 1;
// 	chars_test = malloc(sizeof(char) * (len + 1));
// 	if (!chars_test)
// 		return (0);
// 	i = 0;
// 	cur_char = 'a';
// 	while (i <= 'z' - 'a')
// 		chars_test[i++] = cur_char++;
// 	chars_test[i] = '\0';

// 	gc_add_begin(chars_test);

// 	upper = ft_malloc(sizeof(char) * (len + 1));
// 	if (!upper)
// 		return (-1);
// 	i = -1;
// 	while (++i < len)
// 		upper[i] = 'A' + i;
// 	upper[i] = '\0';
// 	return (1);
// }
