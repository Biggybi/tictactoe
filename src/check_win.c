#include "tictactoe.h"

static int		is_win_x(char grid[], char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < GRIDY)
	{
		n = 0;
		while (n <= GRIDX && grid[n + (i * GRIDY)] == symbol)
			n++;
		if (n == GRIDX)
			return (1);
	}
	return (0);
}

static int		is_win_y(char grid[], char symbol)
{
	int		x;
	int		n;

	x = -1;
	while (++x < GRIDX)
	{
		n = 0;
		while (n <= GRIDY && grid[x + (n * GRIDX)] == symbol)
			n++;
		if (n == GRIDY)
			return (1);
	}
	return (0);
}

static int		is_win_xy(char grid[], char symbol)
{
	int		n;

	if (GRIDX != GRIDY)
		return (0);
	n = 0;
	while (n < GRIDY && grid[n * (GRIDY + 1)] == symbol)
		n++;
	if (n == GRIDY)
		return (1);
	n = 0;
	while (n < GRIDY && grid[GRIDX * (GRIDY - n - 1) + n] == symbol)
		n++;
	if (n == GRIDY)
		return (1);
	return (0);
}

int				is_win(char grid[], int player)
{
	char c;

	c = get_symbol(player);
	return (is_win_y(grid, c) || is_win_x(grid, c) || is_win_xy(grid, c));
}

