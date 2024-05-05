#ifndef TUI_BONUS_H
# define TUI_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include "game.h"

# define CUSTOM_COLORS_START 8
# define MAX_SIZE 5

extern int g_sig;

enum e_const {
	WIN_VALUE = 2048
};

typedef struct s_game
{
	enum e_const win_value;
	WINDOW	*main_w;
	FILE	*save_score;
	bool 	menu;
	// int 	board[MAX_SIZE][MAX_SIZE];
	int		**board;
	int		score;
	int	max_score;
	int		x_max;
	int		y_max;
	int		grid;
	char	dir;
}	t_game;

/*
Warning: terminal too small,
please either resize your terminal,
or press ESCAPE to quit
*/

#endif

