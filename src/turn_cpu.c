#include "tictactoe.h"

static int		minimax(char grid[], int player)
{
	int		move;
	int		score;
	int		i;
	int		newscore;

	move = -1;
	score = -2;
	if (is_win(grid, player))
		return (1);
	if (is_win(grid, -player))
		return (-1);
	i = -1;
	while (++i < GRIDSIZE)
	{
		if(grid[i] == BOXEMPTY)
		{
			grid[i] = get_symbol(player);
			newscore = -minimax(grid, player*-1);
			if(newscore > score)
			{
				score = newscore;
				move = i;
			}
			grid[i] = BOXEMPTY;
		}
	}
	return ((move != -1) * score);
}

static int		move_cpu(char grid[], int player)
{
	int		move;
	int		score;
	int		newscore;
	int		i;

	move = -1;
	score = -2;
	i = -1;
	while (++i < GRIDSIZE)
	{
		if(grid[i] == BOXEMPTY)
		{
			grid[i] = get_symbol(player);
			newscore = -minimax(grid, player*-1);
			grid[i] = BOXEMPTY;
			if(newscore > score)
			{
				score = newscore;
				move = i;
			}
		}
	}
	grid[move] = get_symbol(player);
	return (move);
}

int				turn_cpu(char grid[], int turn, int player)
{
	move_cpu(grid, player);
	print_turn(turn, player);
	print_grid(grid);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

