#include "tictactoe.h"

int		max(int a, int b)
{
	/* return (((a >= b) * a) + ((b > a) * b)); */
	return ((a & -(a >= b)) | (b & -(b > a)));
}

int		min(int a, int b)
{
	/* return (((a <= b) * a) + ((b < a) * b)); */
	return ((a & -(a <= b)) | (b & -(b < a)));
}

char	get_symbol(int player)
{
	if (player == 1)
		return (BOXPLAYER1);
	if (player == -1)
		return (BOXPLAYER2);
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

