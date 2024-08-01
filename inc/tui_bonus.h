#ifndef TUI_BONUS_H
# define TUI_BONUS_H

# ifndef _XOPEN_SOURCE_EXTENDED
#  define _XOPEN_SOURCE_EXTENDED
# endif

# include <locale.h>
# include <unistd.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <wchar.h>
# include "game.h"

# define CUSTOM_COLORS_START 8
# define MAX_SIZE 5
# define GRID_SIZE_4 4
# define GRID_SIZE_5 5
# define FBEST ".scores"
# define BRIGHTNESS_SCALE 0.8
# define RGB_TO_NCURSES_COLOR(rgb) 		((int)((rgb) * BRIGHTNESS_SCALE * 1000 / 255))
# define GET_BOARD_HEIGHT(row, tileWidth) 	((int)(row * tileWidth / 2))
# define GET_BOARD_WIDTH(col, tileWidth) 	((int)(col * tileWidth))

enum e_const {
	WIN_VALUE = 2048
};

typedef struct s_game
{
	enum e_const win_value;
	WINDOW	*main_w;
	FILE	*save_score;
	bool 	menu;
	int		**board;
	int		score;
	int		max_score;
	int		x_max;
	int		y_max;
	int		grid;
	char	dir;
}	t_game;

/** 
 * @brief Launches the game, initializing necessary components and entering the game loop.
 */
int		launch_game(t_game *game);

/** 
 * @brief Initializes the game board and game score, allocates memory for the game board 
 */
void	game_init(t_game *game);

/** 
 * @brief Initializes a menu window to choose a grid size 
*/
int		menu_init(t_game *game);

/** 
 * @brief Runs the main game loop, handling user input and game state updates 
*/
void	game_loop(t_game *game);

/** 
 * @brief  		Processes the game logic for a move in the specified direction.
 * @param game 	A pointer to the t_game structure containing the game state and settings.
 * @param dir 	The direction of the move ('l' for left, 'r' for right, 'u' for up, 'd' for down).
 * @return 		int Returns 1 if no move is made, 0 if a move is made and the game continues, or -1 if the game ends.
*/
int		moves(t_game *game, char dir);

int	display_game_board(t_game* game, int start_y, int start_x, int size, int width);

void	update_game_board(t_game *game);
// void	draw_grid(t_game *game, int y, int x, int width);
void	draw_rectangle(WINDOW *win, int row, int col, int width, int value);
void	draw_border(WINDOW *win, int row, int col, int width, int color);
void	draw_value(WINDOW *win, int row, int col, int value);
int		draw_score(t_game *game, int start_y, int start_x);

/** 
 * @brief  				Calculates the starting x-coordinate (half-width position) 
 * 							for centering an element within a given maximum width.
 * @param maxWidth 		The maximum width available for centering the element.
 * @param elemLength 	The length of the element to be centered.
 * @return 				int representing the x-coordinate from the left edge where the centered element should start. 
 * 						If maxWidth is less than or equal to elemLength, the function returns 0.
*/
int		getHalfWidth(int maxWidth, int elemLength);

/** 
 * @brief  				Prints given message to center of the available the maximum width in given window.
 * @param win			A pointer to the window.
 * @param maxWidth 		The maximum width available for centering the element.
 * @param y_margin 		The starting y-coordinate position to print a message.
 * @param msg			Array of characters to be printed.
*/
int		displayCenteredMsg(WINDOW *win, int y_margin, int maxWidth, char *msg);

void	displayGridSelection(WINDOW *win, int y_margin, int maxWidth, int higlight);

int 	getArrSize(wchar_t **arr);
int		get_box_width(int win_x);
int		loser_wnd(t_game *game);
int		winer_wnd(t_game *game);
int		intlen(int value);
int		is_power_two(int value);
int		get_power(int value);
int 	getMaxLengthWchar_t(wchar_t **arr);

int		read_best_score(void);
void	save_best_score(int best);
void	destroy_board(int **brd, int size);

int		set_random_nbr(t_game *game, int nbr);
int 	get_random_nbr(void);

int		init_colors(void);
void	setup_color_pairs(void);

/*
Warning: terminal too small,
please either resize your terminal,
or press ESCAPE to quit
*/

#endif
