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

void grid_init(s_grid *grid)
{
	int		i;

	grid->len = (GRIDWIDTH + 1) * GRIDHEIGHT;
	grid->width = GRIDWIDTH;
	grid->height = GRIDHEIGHT;

	i = -1;
	grid->str[grid->len] = 0;
	while (++i < grid->len)
		grid->str[i] = '-';
	i = GRIDWIDTH;
	while (i < grid->len)
	{
		grid->str[i] = '\n';
		i += GRIDWIDTH + 1;
	}
}

void play_user(s_grid *grid, int cur_turn)
{
	char	str[100];
	int		choice;

	str[0] = 0;
	while (str[0] < '1' || str[0] > '9' || strlen(str) > 1)
	/* while (str[0] < '1' || str[0] > '9') */
	{
		dprintf(1, "turn: %d\nwhere ? [1-9]\n", cur_turn);
		scanf("%s", str);
		printf("input: %s\n", str);
	}
	choice = str[0] - '0';
	dprintf(1, "height: %d\nwidth: %d\nchoice: %d\n", grid->height, grid->width, choice);
	grid->str[choice - (grid->height - (choice / grid->width))] = 'x';
}

void play_cpu(s_grid *grid);

void play(s_grid *grid)
{
	int		n_turn;
	int		cur_turn;

	n_turn = GRIDWIDTH * GRIDHEIGHT;
	cur_turn = -1;
	while (++cur_turn < n_turn)
	{
		dprintf(1, "c\n");
		play_user(grid, cur_turn);
		/* play_cpu(grid); */
		/* usleep(300); */
		dprintf(1, "%s\n", grid->str);
	}
}

int main(void)
{
	s_grid		grid;
	grid.len = (GRIDWIDTH + 1) * GRIDHEIGHT;

	grid_init(&grid);
	dprintf(1, "%s\n", grid.str);
	play(&grid);
	return (0);
}
