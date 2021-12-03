#include "tictactoe.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <bsd/string.h>

void	grid_init(s_grid *grid)
{
	int		i;

	grid->len = (GRIDWIDTH + 1) * GRIDHEIGHT;
	grid->width = GRIDWIDTH;
	grid->height = GRIDHEIGHT;

	i = -1;
	while (++i < grid->len)
		grid->str[i] = '-';
	i = grid->width;
	while (i < grid->len)
	{
		grid->str[i] = '\n';
		i += grid->width + 1;
	}
	grid->str[grid->len - 1] = 0;
}

int		choice_index(s_grid grid, int choice)
{
	int		i;

	i = choice + grid.width - 1;
	i -= grid.height - ((choice - 1) / grid.width);
	return (i);
}

void	play_user(s_grid *grid)
{
	char	str[100];
	int		choice;

	str[0] = 0;
	while (str[0] < '1' || str[0] > '9' || strlen(str) > 1)
		scanf("%s", str);
	choice = str[0] - '0';
	/* dprintf(1, "height: %d\nwidth: %d\nchoice: %d\n", grid->height, grid->width, choice); */
	grid->str[choice_index(*grid, choice)] = 'x';
}

void	play_cpu(s_grid *grid)
{
	grid->str[choice_index(*grid, rand() % 10)] = 'o';
}

void	play(s_grid *grid)
{
	int		n_turn;
	int		cur_turn;
	void	(*player1)(s_grid*);
	void	(*player2)(s_grid*);

	player1 = &play_user;
	player2 = &play_cpu;
	n_turn = grid->width * grid->height;
	dprintf(1, "n_turn: %d\n", n_turn);
	cur_turn = -1;
	while (++cur_turn < n_turn)
	{
		dprintf(1, "==== turn: %d ====\n", cur_turn + 1);
		player1(grid);
		player2(grid);
		dprintf(1, "%s\n", grid->str);
	}
}

int main(void)
{
	s_grid		grid;

	grid_init(&grid);
	dprintf(1, "grid->width: %d\n", grid.width);
	dprintf(1, "grid->height: %d\n", grid.height);
	dprintf(1, "grid->total: %d\n", grid.len);
	dprintf(1, "%s\n", grid.str);
	play(&grid);
	return (0);
}
