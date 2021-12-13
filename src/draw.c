#include "tictactoe.h"

static void	line_init(char line[GRIDX * 4 + 2], char empty, char sep)
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

static void	line_symbols(char grid[], char line[GRIDX * 4 + 2], int idx)
{
	int		i;

	i = -2;
	while ((i+=4) < GRIDX * 4)
		line[i] = grid[(GRIDX * idx) + (i / 4)];
}

static void	line_outer_init(char line[GRIDX * 4 + 2], char inner, char outer)
{
	int		i;

	line[GRIDX * 4 + 1] = 0;
	line[GRIDX * 4] = inner;
	line[0] = inner;
	i = 0;
	while (++i < GRIDX * 4)
		line[i] = outer;
}

void		print_grid(char grid[])
{
	int		i;
	char	line_deco_outer[GRIDX * 4 + 2];
	char	line_deco_inner[GRIDX * 4 + 2];
	char	line_grid[GRIDX * 4 + 2];

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

void		print_turn(int turn, int player)
{
	system("clear");
	printf("====  turn %d  |  player %d  ====\n", turn + 1, player);
}

int			print_win(char grid[], int turn, int player)
{
	system("clear");
	print_turn(turn, player);
	print_grid(grid);
	printf("Player%d won!\n", player);
	return (player);
}

