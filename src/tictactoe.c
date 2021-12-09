#include "tictactoe.h"
#include <stdio.h>

void	grid_init(char grid[GRIDLEN])
{
	int		i;

	i = -1;
	while (++i < GRIDLEN)
		grid[i] = BOXEMPTY;
	i = -1;
	while (i < GRIDLEN - GRIDX)
	{
		i += GRIDX + 1;
		grid[i] = '\n';
	}
	grid[GRIDLEN - 1] = 0;
}

int		get_index(int move)
{
	int		idx;

	idx = move + GRIDY - 1 - GRIDX + ((move - 1) / GRIDY);
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
	while (++i < GRIDY)
	{
		n = -1;
		while (++n <= GRIDX && grid[i + (n * (GRIDY + 1))] == symbol)
			;
		if (n == GRIDX)
			return (1);
	}
	return (0);
}

int		is_win_y(char grid[GRIDLEN], char symbol)
{
	int		i;
	int		n;

	i = -1;
	while (++i < GRIDX)
	{
		n = -1;
		while (++n <= GRIDY && grid[n + (i * (GRIDX + 1))] == symbol)
			;
		if (n == GRIDY)
			return (1);
	}
	return (0);
}

int		is_win_xy(char grid[GRIDLEN], char symbol)
{
	int		n;

	if (GRIDX != GRIDY)
		return (0);
	n = -1;
	while (++n <= GRIDY && grid[n * (GRIDY + 2)] == symbol)
		;
	if (n == GRIDY)
		return (1);
	n = -1;
	while (++n <= GRIDY && grid[(GRIDY * (GRIDY - n)) - 1] == symbol)
		;
	if (n == GRIDY)
		return (1);
	return (0);
}

int		is_win(char grid[GRIDLEN], int player)
{
	char c;

	c = get_symbol(player);
	return (is_win_y(grid, c) || is_win_x(grid, c) || is_win_xy(grid, c));
}

void	print_grid(char grid[GRIDLEN])
{
	int		i;
	char	edgesline[GRIDX * 4 + 2];
	char	interline[GRIDX * 4 + 2];

	interline[GRIDX * 4 + 1] = 0;
	edgesline[GRIDX * 4 + 1] = 0;
	edgesline[GRIDX * 4] =  '+';
	edgesline[0] = '+';
	i = 0;
	while (++i < GRIDX * 4)
		edgesline[i] = '-';
	i = -1;
	while (++i < GRIDX * 4 + 1)
		interline[i] = '-';
	i = -4;
	while ((i+=4) < GRIDX * 4 + 1)
		interline[i] = '|';
	printf("\n%s\n", edgesline);
	i = -1;
	while (++i < GRIDLEN - 1)
		if (i > 0 && (i + 1) % (GRIDX + 1) == 0)
			printf("|\n%s\n", interline);
		else
			printf("| %c ", grid[i]);
	printf("|\n%s\n", edgesline);
}

void	print_turn(int turn)
{
	system("clear");
	printf("==== turn %d ====\n", turn + 1);
}

int		turn_user(char grid[GRIDLEN], int turn, int player)
{
	char	str[100];
	int		idx;

	str[0] = 0;
	while (!str[0])
	{
		print_turn(turn);
		print_grid(grid);
		printf("What's your play ? [1-9]\n");
		scanf("%s", str);
		/* Note: Should atoi this shit */
		idx = get_index(str[0] - '0');
		if (str[0] < '1' || str[0] > '9' || strlen(str) > 1 || idx < 0 || grid[idx] != BOXEMPTY)
		{
			printf("Wrong position: '%s'. ", str);
			str[0] = 0;
		}
	}
	grid[idx] = get_symbol(player);
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
			/* dprintf(1, "%d\n", score); */
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
	print_grid(grid);
	usleep(PAUSETIME);
	return (is_win(grid, player));
}

int		print_win(char grid[GRIDLEN], int player, int turn)
{
	system("clear");
	print_turn(turn);
	print_grid(grid);
	printf("Player%d won!\n", player);
	return (player);
}

int		play(char grid[GRIDLEN])
{
	int		turn;
	int		(*turn_p1)(char[], int, int);
	int		(*turn_p2)(char[], int, int);

	turn_p1 = &turn_cpu;
	turn_p2 = &turn_cpu;
	/* turn_p2 = &turn_cpu; */
	turn = -1;
	while (++turn < GRIDSIZE)
		if (turn_p1(grid, turn, 1) == 1)
			return (print_win(grid, 1, turn));
		else if (++turn < GRIDSIZE - (GRIDSIZE % 2))
			if (turn_p2(grid, turn, -1) == 1)
				return (print_win(grid, 2, turn));
	printf("Draw.\n");
	return (0);
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

int main(void)
{
	char	grid[GRIDLEN];
	char	re[1];

	re[0] = 13;
	while (re[0] == 13 || re[0] == 'y' || !re[0])
	{
		system("clear");
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

