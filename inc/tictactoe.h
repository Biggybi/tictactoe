#ifndef TICTACTOE_H
# define TICTACTOE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

double log2(double x);
float log2f(float x);
long double log2l(long double x);

# define GRIDX 3
# define GRIDY 3
# define GRIDSIZE GRIDY * GRIDX
# define GRIDLEN (GRIDY + 1) * GRIDX
# define BOXEMPTY '-'
# define BOXPLAYER1 'x'
# define BOXPLAYER2 'o'
# define PAUSETIME 0

#endif
