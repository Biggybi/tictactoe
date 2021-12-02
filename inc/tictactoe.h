#ifndef TICTACTOE_H
# define TICTACTOE_H

# define GRIDHEIGHT 3
# define GRIDWIDTH 3

typedef struct	t_grid {
	char	str[(GRIDWIDTH + 1) * GRIDHEIGHT];
	int		width;
	int		height;
	int		len;
}				s_grid;

#endif
