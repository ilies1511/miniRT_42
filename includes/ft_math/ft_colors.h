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

typedef union u_uint_color
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
}	__attribute__((packed))t_uint_color;

//t_f_color can be cast to t_vec / t_tuple with this layout
//(x->r, y->g, z->b, w->a)
typedef struct s_f_color
{
	float	r;
	float	g;
	float	b;
	float	a;	//not used in the book as far as I saw
				//to enable casting to t_vec should be left as 0.0
				//when converting to t_uint_color should be treated as 1.0
}	t_f_color;
// ___t_f_color specific implementation needed________
//Hadamard product (or Schur product)
t_f_color		fcol_fcol_mult(t_f_color a, t_f_color b);
t_uint_color	fcolor_to_uintcolor(t_f_color fcolor);

/*______________________________________________________
 These should not be needed since the tuple/vec operations can be applyied
 for performace or debugging we could implement these to cut down operations
 or make type specific asserts
*/
t_f_color		fcol_add(t_f_color a, t_f_color b);
t_f_color		fcol_sub(t_f_color a, t_f_color b);
t_f_color		fcol_mult(t_f_color color, float scalar);

#endif //FT_COLORS_H
