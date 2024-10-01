#ifndef FT_COLORS_H
# define FT_COLORS_H

# include <stdint.h>
# include <stdbool.h>
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

typedef union u_uintcolor
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
}	__attribute__((packed))t_uintcolor;

typedef struct s_fcolor
{
	double	r;
	double	g;
	double	b;
	double	a;	//not used in the book as far as I saw
				//to enable casting to t_vec should be left as 0.0
				//when converting to t_uintcolor should be treated as 1.0
}	t_fcolor;

t_fcolor		fcolor_white(void);
t_fcolor		fcolor_black(void);

t_fcolor		new_fcolor(double r, double g, double b, double a);
t_uintcolor		fcolor_to_uintcolor(t_fcolor fcolor);
t_fcolor		add_fcolor(t_fcolor a, t_fcolor b);
t_fcolor		sub_fcolor(t_fcolor a, t_fcolor b);
t_fcolor		scale_fcolor(t_fcolor c, double scalar);
/*
	Hadamard product (or Schur product)
	Multiplacation of two colors;
*/
t_fcolor		mult_fcolor(t_fcolor a, t_fcolor b);
bool			eq_fcolor(t_fcolor a, t_fcolor b);
void			print_fcolor(char *str, t_fcolor col);

#endif //FT_COLORS_H
