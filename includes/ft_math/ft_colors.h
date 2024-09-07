#ifndef FT_COLORS_H
# define FT_COLORS_H

# include <stdint.h>
//color defines for the full field of the t_color union on little endian systems
# ifndef BLACK
#  define BLACK 0xFF000000
# endif
# ifndef RED
#  define RED 0xFF0000FF
# endif
# ifndef GREEN
#  define GREEN 0xFF00FF00
# endif
# ifndef BLUE
#  define BLUE 0xFFFF0000
# endif
# ifndef MAGENTA
#  define MAGENTA 0xFFFF00FF
# endif
# ifndef YELLOW
#  define YELLOW 0xFF00FFFF
# endif
# ifndef WHITE
#  define WHITE 0xFFFFFFFF
# endif
# ifndef CYAN
#  define CYAN 0xFF00FFFF
# endif
# ifndef PURPLE
#  define PURPLE 0xFFFF00A0
# endif
# ifndef ORANGE
#  define ORANGE 0xFF0080FF
# endif
# ifndef TEAL
#  define TEAL 0xFF808000
# endif
# ifndef PINK
#  define PINK 0xFFFF80FF
# endif
# ifndef LIME
#  define LIME 0xFF80FF00
# endif
# ifndef LIGHT_GREY
#  define LIGHT_GREY 0xFFD3D3D3
# endif
# ifndef DARK_GREY
#  define DARK_GREY 0xFFA9A9A9
# endif

typedef union u_color
{
	uint8_t		bytes[4];
	uint32_t	full;
	struct
	{
			uint8_t	r;
			uint8_t	g;
			uint8_t	b;
			uint8_t	a;
	}	__attribute__((packed))argb;
}	__attribute__((packed))t_color;


#endif //FT_COLORS_H
