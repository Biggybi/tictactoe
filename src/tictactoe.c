#include "tictactoe.h"
#include <stdio.h>

void	grid_init(char grid[GRIDLEN])
{
	int		i;

	i = -1;
	while (++i < GRIDLEN)
		grid[i] = BOXEMPTY;
	i = -1;
	while (i < GRIDLEN - GRIDY)
	{
		i += GRIDY + 1;
		grid[i] = '\n';
	}
	grid[GRIDLEN - 1] = 0;
}

int		get_index(int move)
{
	int		idx;

	idx = move + GRIDX - 1 - (GRIDY - ((move - 1) / GRIDX));
	return (idx);
}

char	get_symbol(int player)
{
	if (player == 1)
		return (BOXPLAYER1);
	if (player == -1)
		return (BOXPLAYER2);
	return (0);
}

int		is_win_x(char grid[GRIDLEN], char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < GRIDX)
	{
		n = -1;
		while (++n <= GRIDY && grid[i + (n * (GRIDX + 1))] == symbol)
			;
		if (n == GRIDY)
			return (1);
	}
	return (0);
}

int		is_win_y(char grid[GRIDLEN], char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < GRIDY)
	{
		n = -1;
		while (++n <= GRIDX && grid[n + (i * (GRIDY + 1))] == symbol)
			;
		if (n == GRIDX)
			return (1);
	}
	return (0);
}

int		is_win_xy(char grid[GRIDLEN], char symbol)
{
	int		n;

	if (GRIDY != GRIDX)
		return (0);
	n = -1;
	while (++n <= GRIDX && grid[n * (GRIDX + 2)] == symbol)
		;
	if (n == GRIDX)
		return (1);
	n = -1;
	while (++n <= GRIDX && grid[(GRIDX * (GRIDX - n)) - 1] == symbol)
		;
	if (n == GRIDX)
		return (1);
	return (0);
}

int		is_win(char grid[GRIDLEN], int player)
{
	char c;

	c = get_symbol(player);
	return (is_win_y(grid, c) || is_win_x(grid, c) || is_win_xy(grid, c));
}

void	print_turn(int turn)
{
	system("clear");
	dprintf(1, "==== turn %d ====\n", turn + 1);
}

int		turn_user(char grid[GRIDLEN], int turn, int player)
{
	char	str[100];
	int		idx;

	str[0] = 0;
	while (!str[0])
	{
		dprintf(1, "What's your play ? [1-9]\n");
		scanf("%s", str);
		/* Note: Should atoi this shit */
		idx = get_index(str[0] - '0');
		if (str[0] < '1' || str[0] > '9' || strlen(str) > 1 || idx < 0 || grid[idx] != BOXEMPTY)
		{
			system("clear");
			dprintf(1, "%s\n\n", grid);
			dprintf(1, "Wrong position: '%s'. ", str);
			str[0] = 0;
		}
	}
	grid[idx] = get_symbol(player);
	print_turn(turn);
	dprintf(1, "%s\n\n", grid);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

int		minimax(char grid[GRIDLEN], int player)
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
	while (++i < GRIDLEN)
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

int		move_cpu(char grid[GRIDLEN], int player)
{
	int		move;
	int		score;
	int		newscore;
	int		i;

	move = -1;
	score = -2;
	i = -1;
	while (++i < GRIDLEN)
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

int		turn_cpu(char grid[GRIDLEN], int turn, int player)
{
	move_cpu(grid, player);
	print_turn(turn);
	dprintf(1, "%s\n\n", grid);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

int		print_win(int player)
{
	dprintf(1, "Player%d won!\n", player);
	return(player);
}

int		play(char grid[GRIDLEN])
{
	int		turn;
	int		(*turn_p1)(char[], int, int);
	int		(*turn_p2)(char[], int, int);

	turn_p1 = &turn_cpu;
	turn_p2 = &turn_cpu;
	turn = -1;
	while (++turn < GRIDSIZE)
		if (turn_p1(grid, turn, 1) == 1)
			return (print_win(1));
		else if (++turn < GRIDSIZE - (GRIDSIZE % 2))
			if (turn_p2(grid, turn, -1) == 1)
				return (print_win(2));
	dprintf(1, "Draw.");
	return (0);
}

int main(void)
{
	char	grid[(GRIDY + 1) * GRIDX];
	char	re[1];

	re[0] = 13;
	while (re[0] == 13 || re[0] == 'y' || !re[0])
	{
		system("clear");
		dprintf(1, "New Tic-tac-toe Game!\n");
		grid_init(grid);
		dprintf(1, "%s\n", grid);
		play(grid);
		dprintf(1, "Play again? [y/n]\n-> ");
		scanf("%s", re);
		/* fgets(re, 100, stdin); */
	}
	return (0);
}

