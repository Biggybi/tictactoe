#ifndef TICTACTOE_H
# define TICTACTOE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int		is_win(char grid[], int player);
int		print_win(char grid[], int turn, int player);
void	print_grid(char grid[]);
void	print_turn(int turn, int player);
int		turn_cpu(char grid[], int turn, int player);
int		turn_user(char grid[], int turn, int player);
char	get_symbol(int player);
int		intlen(int n);
int		max(int a, int b);
int		min(int a, int b);

# define GRIDX 3
# define GRIDY 3
# define GRIDSIZE GRIDY * GRIDX
# define BOXEMPTY '-'
# define BOXPLAYER1 'x'
# define BOXPLAYER2 'o'
# define PAUSETIME 0

#endif
