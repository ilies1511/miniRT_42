#ifndef FT_FLOATS_H
# define FT_FLOATS_H

# include <stdbool.h>

# ifndef EPSILON //precision to compare 2 floats
#  define EPSILON ((float)0.00001)
# endif

//equal float
//(a == b) ?
bool	eq_f(float a, float b);

#endif //FT_FLOATS_H
