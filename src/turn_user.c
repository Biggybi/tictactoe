#include "tictactoe.h"

int		turn_user(char grid[], int turn, int player)
{
	char	str[intlen(GRIDSIZE)];
	int		idx;
	int		input;

	idx = 0;
	bzero(str, intlen(GRIDSIZE));
	while (!str[0])
	{
		print_turn(turn, player);
		print_grid(grid);
		if (idx == -1)
			printf("Wrong position: '%d'. ", input);
		printf("What's your play ? [1-%d]\n> ", GRIDSIZE);
		scanf("%s", str);
		input = atoi(str);
		idx = input - 1;
		if (input < 0 || input > GRIDSIZE || grid[idx] != GRIDEMPTY)
		{
			bzero(str, intlen(GRIDSIZE));
			idx = -1;
		}
	}
	grid[idx] = get_symbol(player);
	usleep(DELAY);
	return (is_win(grid, player));
}

