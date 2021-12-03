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
#include <time.h>

void	grid_init(s_grid *grid)
{
	int		i;

	srand(time(0));
	grid->slen = (GRIDWIDTH + 1) * GRIDHEIGHT;
	grid->x = GRIDWIDTH;
	grid->y = GRIDHEIGHT;
	grid->size = grid->x * grid->y;

	i = -1;
	while (++i < grid->slen)
		grid->str[i] = BOXEMPTY;
	i = grid->x;
	while (i < grid->slen)
	{
		grid->str[i] = '\n';
		i += grid->x + 1;
	}
	grid->str[grid->slen - 1] = 0;
}

int		get_index(s_grid grid, int choice)
{
	int		idx;

	idx = choice + grid.x - 1;
	idx -= grid.y - ((choice - 1) / grid.x);
	return (idx);
}

int		is_win_column(s_grid grid, char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < grid.x)
	{
		n = -1;
		while (++n <= grid.y && grid.str[i + (n * (grid.x + 1))] == symbol)
			;
		if (n == grid.y)
			return (1);
	}
	return (0);
}

int		is_win_line(s_grid grid, char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < grid.y)
	{
		n = -1;
		while (++n <= grid.x && grid.str[n + (i * (grid.y + 1))] == symbol)
			;
		if (n == grid.x)
			return (1);
	}
	return (0);
}

int		is_win_diagonal(s_grid grid, char symbol)
{
	int		n;

	if (grid.y != grid.x)
		return (0);
	n = -1;
	while (++n <= grid.x && grid.str[n + n + n * grid.x] == symbol)
		;
	if (n == grid.x)
		return (1);
	n = -1;
	while (++n <= grid.x && grid.str[(grid.x * (grid.x - n)) - 1] == symbol)
		;
	if (n == grid.x)
		return (1);
	return (0);
}

int		is_win(s_grid grid, char symbol)
{
	return (is_win_line(grid, symbol)\
			|| is_win_column(grid, symbol)\
			|| is_win_diagonal(grid, symbol));
}

void	fill_box(s_grid *grid, int idx, char fillchar)
{
	grid->str[idx] = fillchar;
}

int		play_user(s_grid *grid, char symbol)
{
	char	str[100];
	int		idx;

	str[0] = 0;
	while (!*str)
	{
		dprintf(1, "What's your play ? [1-9]\n");
		scanf("%s", str);
		idx = get_index(*grid, str[0] - '0');
		if (str[0] < '1' || str[0] > '9' || strlen(str) > 1 || idx < 0)
		{
			dprintf(1, "Wrong position: '%s'. ", str);
			str[0] = 0;
		}
	}
	fill_box(grid, idx, symbol);
	return (is_win(*grid, symbol));
}

int		play_cpu(s_grid *grid, char symbol, int turn)
{
	int		idx;
	int		try;

	idx = -1;
	try = rand() % (grid->y * grid->x);
	idx = get_index(*grid, try);
	while (grid->str[idx] != BOXEMPTY)
	{
		if (idx == grid->slen - 1)
			idx = -1;
		idx++;
		/* dprintf(1, "l"); */
	}
	system("clear");
	dprintf(1, "==== turn: %d ====\n", turn + 1);
	fill_box(grid, idx, symbol);
	dprintf(1, "%s\n\n", grid->str);
	usleep(1000000);
	return (is_win(*grid, symbol));
}

int		print_win(int player)
{
	dprintf(1, "Player%d won!\n", player);
	return(player);
}

int		play(s_grid *grid)
{
	int		turn;
	int		(*player1)(s_grid*, char, int);
	int		(*player2)(s_grid*, char, int);

	player1 = &play_cpu;
	player2 = &play_cpu;
	turn = -1;
	while (++turn < grid->size)
	{
		if (player1(grid, BOXPLAYER1, turn) == 1)
			return (print_win(1));
		system("clear");
		if (++turn < grid->size - 1)
			if (player2(grid, BOXPLAYER2, turn) == 1)
				return (print_win(2));
	}
	dprintf(1, "Draw.");
	return (0);
}

int main(void)
{
	s_grid		grid;

	grid_init(&grid);
	dprintf(1, "grid->x: %d\n", grid.x);
	dprintf(1, "grid->height: %d\n", grid.y);
	dprintf(1, "grid->total: %d\n", grid.slen);
	dprintf(1, "%s\n", grid.str);
	play(&grid);
	return (0);
}

