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
# define FBEST ".scores"

extern int g_sig;

enum e_const {
	WIN_VALUE = 8
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


int		game_loop(t_game *game);
void	start_game(int sig);
void	game_init(t_game *game);
int		get_box_width(int win_x);
void	draw_rectangle(WINDOW *win, int row, int col, int width, int value);
void	draw_cell(WINDOW *win, int row, int col, int width, int value);
void	draw_value(WINDOW *win, int row, int col, int value);
int		loser_wnd(t_game *game);
int		winer_wnd(t_game *game);
void	draw_grid(t_game *game, int y, int x, int width);
void	grid(t_game *game);
int		intlen(int value);
int		draw_score(t_game *game, int start_y, int start_x);
/*
Warning: terminal too small,
please either resize your terminal,
or press ESCAPE to quit
*/

#endif

