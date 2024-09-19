#ifndef FT_FLOATS_H
# define FT_FLOATS_H

# include <float.h>
# include <stdbool.h>
# include <math.h>

# ifndef EPSILON //precision to compare 2 floats
#  define EPSILON ((float)0.001)
# endif

//equal float
//(a == b) ?
bool	eq_f(float a, float b);
bool	less_eq_f(float a, float b);
bool	greater_eq_f(float a, float b);
float	clamp_f(float nb, float min, float max);

#endif //FT_FLOATS_H
