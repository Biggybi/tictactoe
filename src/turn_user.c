#include "tictactoe.h"

int		turn_user(char grid[], int turn, int player)
{
	char	str[intlen(GRIDSIZE)];
	int		idx;
	int		input;
	int		wrong_input;

	wrong_input = 0;
	bzero(str, intlen(GRIDSIZE));
	while (!str[0])
	{
		print_turn(turn, player);
		print_grid(grid);
		if (wrong_input)
			printf("Wrong position: '%d'. ", input);
		printf("What's your play ? [1-%d]\n", GRIDSIZE);
		wrong_input = 0;
		scanf("%s", str);
		input = atoi(str);
		idx = input - 1;
		if (input < 0 || input > GRIDSIZE || grid[idx] != BOXEMPTY)
		{
			bzero(str, intlen(GRIDSIZE));
			wrong_input = 1;
		}
	}
	grid[idx] = get_symbol(player);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

