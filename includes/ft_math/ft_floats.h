#ifndef FT_FLOATS_H
# define FT_FLOATS_H

# include <float.h>
# include <stdbool.h>
# include <math.h>
# include <stdint.h>
# include <stdlib.h>

# ifndef EPSILON //precision to compare 2 floats
#  define EPSILON ((float)0.0001)
# endif

//equal float
//(a == b) ?
bool	eq_f(float a, float b);
bool	less_eq_f(float a, float b);
bool	greater_eq_f(float a, float b);
float	clamp_f(float nb, float min, float max);

// returns the sum of the nbs arre with increased precision
double	kahan_sum(double *nbs, size_t count);

#endif //FT_FLOATS_H
