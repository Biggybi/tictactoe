#include "tictactoe.h"
#include <stdio.h>

void	grid_init(char grid[])
{
	int		i;

	i = -1;
	while (++i < GRIDSIZE)
		grid[i] = GRIDEMPTY;
	grid[i] = 0;
}

int		play(char grid[])
{
	int		turn;
	int		(*turn_p1)(char[], int, int);
	int		(*turn_p2)(char[], int, int);

	turn_p1 = &turn_user;
	turn_p2 = &turn_cpu;
	turn = -1;
	while (++turn < GRIDSIZE)
		if (turn_p1(grid, turn, 1) == 1)
			return (print_win(grid, turn, 1));
		else if (++turn < GRIDSIZE - (GRIDSIZE % 2))
			if (turn_p2(grid, turn, -1) == 1)
				return (print_win(grid, turn, 2));
	printf("Draw.\n");
	return (0);
}

int		main(void)
{
	char	grid[GRIDSIZE + 1];
	char	re[1];

	re[0] = 13;
	while (re[0] == 13 || re[0] == 'y' || !re[0])
	{
		system("clear");
		printf("New Tic-tac-toe Game!\n");
		grid_init(grid);
		print_grid(grid);
		play(grid);
		printf("Play again? [yes/no]\n> ");
		scanf("%s", re);
		/* fgets(re, 100, stdin); */
	}
	printf("Goodbye!\n\n");
	return (0);
}

