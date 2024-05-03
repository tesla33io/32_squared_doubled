#ifndef TUI_BONUS_H
# define TUI_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <ncurses.h>
# include "../libft/libft.h"
# include <time.h>
# include <signal.h>
# include <fcntl.h>

extern int g_sig;

enum e_const {
	WIN_VALUE = 2048
};

typedef struct s_game
{
	enum e_const win_value;
	bool menu;
	int	choice;
	int **board;
	int score;
	int	x_max;
	int	y_max;
	
}	t_game;



#endif

