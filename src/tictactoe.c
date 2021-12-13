#include "tictactoe.h"
#include <stdio.h>

void	grid_init(char grid[])
{
	int		i;

	i = -1;
	while (++i < GRIDSIZE)
		grid[i] = BOXEMPTY;
	grid[i] = 0;
	/* grid[GRIDSIZE - 1] = 0; */
}

char	get_symbol(int player)
{
	if (player == 1)
		return (BOXPLAYER1);
	if (player == -1)
		return (BOXPLAYER2);
	return (0);
}

int		is_win_x(char grid[], char symbol)
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

int		is_win_y(char grid[], char symbol)
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

int		is_win_xy(char grid[], char symbol)
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

int		is_win(char grid[], int player)
{
	char c;

	c = get_symbol(player);
	return (is_win_y(grid, c) || is_win_x(grid, c) || is_win_xy(grid, c));
	/* return (is_win_y(grid, c) || is_win_x(grid, c)); */
}

void	line_init(char line[GRIDX * 4 + 2], char empty, char sep)
{
	int		i;

	line[GRIDX * 4 + 1] = 0;
	i = -1;
	while (++i < GRIDX * 4 + 1)
		line[i] = empty;
	i = -4;
	while ((i+=4) < GRIDX * 4 + 1)
		line[i] = sep;
}

void	line_symbols(char grid[], char line[GRIDX * 4 + 2], int idx)
{
	int		i;

	i = -2;
	while ((i+=4) < GRIDX * 4)
		line[i] = grid[(GRIDX * idx) + (i / 4)];
}

void	line_outer_init(char line[GRIDX * 4 + 2], char inner, char outer)
{
	int		i;

	line[GRIDX * 4 + 1] = 0;
	line[GRIDX * 4] = inner;
	line[0] = inner;
	i = 0;
	while (++i < GRIDX * 4)
		line[i] = outer;
}

void	print_grid(char grid[])
{
	int		i;
	char	line_deco_outer[GRIDX * 4 + 2];
	char	line_deco_inner[GRIDX * 4 + 2];
	char	line_grid[GRIDX * 4 + 2];

	dprintf(1, "print grid\n");
	line_outer_init(line_deco_outer, '+', '-');
	line_init(line_grid, ' ', '|');
	line_init(line_deco_inner, '-', '|');
	printf("\n%s\n", line_deco_outer);
	i = -1;
	while (++i < GRIDY)
	{
		line_symbols(grid, line_grid, i);
		printf("%s\n", line_grid);
		if (i != GRIDY - 1)
			printf("%s\n", line_deco_inner);
	}
	printf("%s\n", line_deco_outer);
}

void	print_turn(int turn, int player)
{
	/* system("clear"); */
	printf("====  turn %d  |  player %d  ====\n", turn + 1, player);
}

int		intlen(int n)
{
	int		i;

	if (n == -2147483648)
		return (11);
	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n /= 10)
		i++;
	return (i + 1);
}

int		turn_user(char grid[], int turn, int player)
{
	char	str[intlen(GRIDSIZE)];
	int		idx;
	int		input;

	bzero(str, intlen(GRIDSIZE));
	while (!str[0])
	{
		print_turn(turn, player);
		print_grid(grid);
		printf("What's your play ? [1-%d]\n", GRIDSIZE);
		scanf("%s", str);
		input = atoi(str);
		idx = input - 1;
		if (input < 0 || input > GRIDSIZE || grid[idx] != BOXEMPTY)
		{
			printf("Wrong position: '%s'. ", str);
			bzero(str, intlen(GRIDSIZE));
		}
	}
	grid[idx] = get_symbol(player);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

int		minimax(char grid[], int player)
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

int		move_cpu(char grid[], int player)
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

int		turn_cpu(char grid[], int turn, int player)
{
	move_cpu(grid, player);
	print_turn(turn, player);
	print_grid(grid);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

int		print_win(char grid[], int turn, int player)
{
	/* system("clear"); */
	print_turn(turn, player);
	print_grid(grid);
	printf("Player%d won!\n", player);
	return (player);
}

int		play(char grid[])
{
	int		turn;
	int		(*turn_p1)(char[], int, int);
	int		(*turn_p2)(char[], int, int);

	turn_p1 = &turn_user;
	turn_p2 = &turn_user;
	/* turn_p2 = &turn_cpu; */
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

/* int		intlen(int n) */
/* { */
/* 	int		i; */

/* 	if (n == -2147483648) */
/* 		return (11); */
/* 	i = 0; */
/* 	if (n < 0) */
/* 	{ */
/* 		n = -n; */
/* 		i++; */
/* 	} */
/* 	while (n /= 10) */
/* 		i++; */
/* 	return (i + 1); */
/* } */

int main(void)
{
	char	grid[GRIDSIZE];
	char	re[1];

	re[0] = 13;
	while (re[0] == 13 || re[0] == 'y' || !re[0])
	{
		/* system("clear"); */
		printf("New Tic-tac-toe Game!\n");
		grid_init(grid);
		print_grid(grid);
		play(grid);
		printf("Play again? [yes/no]\n-> ");
		scanf("%s", re);
		/* fgets(re, 100, stdin); */
	}
	return (0);
}

