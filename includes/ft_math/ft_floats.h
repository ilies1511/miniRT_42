#ifndef FT_FLOATS_H
# define FT_FLOATS_H

// # include <double.h>
# include <float.h>
# include <stdbool.h>
# include <math.h>
# include <stdint.h>
# include <stdlib.h>

# ifndef EPSILON //precision to compare 2 floats
#  define EPSILON ((double)0.0001)
# endif

//equal double
//(a == b) ?
bool	eq_f(double a, double b);
bool	less_eq_f(double a, double b);
bool	greater_eq_f(double a, double b);
double	clamp_f(double nb, double min, double max);

// returns the sum of the nbs arre with increased precision
double	kahan_sum(double *nbs, size_t count);

#endif //FT_FLOATS_H
