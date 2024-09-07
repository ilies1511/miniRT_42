#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include <stdlib.h>
# include <stdint.h>

typedef struct s_main		t_main;
typedef union u_uint_color	t_uint_color;

void	put_pixel(size_t x, size_t y, t_uint_color color, uint32_t *pixels);

#endif //MLX_INTERFACE_H
