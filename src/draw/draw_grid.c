#include "../../inc/tui_bonus.h"
#include "../../inc/titles.h"
#include <ncurses.h>
#include <unistd.h>

void	update_game_board(t_game *game)
{
	int	size = game->grid;
	int	start_x, start_y, width, tmp_x;
	int top_margin = 2;

	wclear(game->main_w);
	getmaxyx(game->main_w, game->y_max, game->x_max);
	if (game->y_max < 24 || game->x_max < 54)
	{
		wclear(game->main_w);
		wprintw(game->main_w, "Warning: terminal too small, please either resize your terminal or press ESCAPE to quit");
		return ;
	}
	start_y = top_margin;
	displayGameTitle(game->main_w, TITLE_SMALL, game->x_max, start_y);
	tmp_x = game->x_max;
	if (tmp_x > 105)
		tmp_x = 104;
	width = (tmp_x - 1) / (size + 2);
	if ((width * (size + 2)) >= (game->x_max) || (width * (size + 2)) >= (game->y_max))
		width = game->y_max / size + 2;
	if ((width % 2) != 0)
		width -= width % 2;
	start_x = (game->x_max - 1) / 2 - ((width * size) / 2);
	start_y = start_y + getArrSize(titles[TITLE_SMALL].titleText) + top_margin;
	int score_offset = draw_score(game, start_y, start_x + (width * size));
	start_y = start_y + score_offset + top_margin;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			draw_border(game->main_w, start_y + (row * width / 2), start_x + (col * width), width, CUSTOM_COLORS_START + 14);
			draw_rectangle(game->main_w, start_y + (row * width / 2), start_x + (col * width), width, game->board[row][col]);
			draw_value(game->main_w, 
				start_y + (row * width / 2) + width / 4, 
				start_x + col * width + (width / 2) - intlen(game->board[row][col]) / 2, 
				game->board[row][col]);
		}
	}
	wrefresh(game->main_w);
}

unsigned int nextPowerOfTwo(unsigned int n) {
    if (n == 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

void	display_mini_game_board(t_game* game, int start_y, int start_x, int size, int width)
{
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			int random = rand() % 2048;
			if (!is_power_two(random))
				random = nextPowerOfTwo(random);
			draw_border(game->main_w, start_y + (row * width / 2), start_x + (col * width), width, CUSTOM_COLORS_START + 14);
			draw_rectangle(game->main_w, start_y + (row * width / 2), start_x + (col * width), width, random);
			draw_value(game->main_w, 
				start_y + (row * width / 2) + width / 4, 
				start_x + col * width + (width / 2) - intlen(random) / 2, 
				random);
		}
	}
}

void	draw_border(WINDOW *win, int row, int col, int width, int color)
{
	wattron(win, COLOR_PAIR(color) | A_BOLD | A_REVERSE);
	mvwhline(win, row, col, ' ', width);
	mvwhline(win, row + width / 2, col, ' ', width);
	mvwvline(win, row, col, ' ', width / 2);
	mvwvline(win, row, col + width, ' ', width / 2);
	mvwaddch(win, row, col, ' ');
	mvwaddch(win, row + width / 2, col, ' ');
	mvwaddch(win, row + width / 2, col + width, ' ');
	mvwaddch(win, row, col + width, ' ');
	wattroff(win, COLOR_PAIR(color) | A_BOLD | A_REVERSE);
}

void	draw_rectangle(WINDOW *win, int row, int col, int width, int value)
{
	int y = 0;
	int x = 0;
	int	power = get_power(value);

	wattron(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_REVERSE);
	for (y = row + 1; y < row + width - (width / 2); y++) {
		for (x = col + 1; x < col + width; x++) {
			mvwaddch(win, y, x, ' ');
		}
	}
	wattroff(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_REVERSE);
}

void	draw_value(WINDOW *win, int row, int col, int value)
{
	if (value <= 0)
		return ;
	int	power = get_power(value);
	wattron(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_BOLD | A_REVERSE);
	mvwprintw(win, row, col, "%i", value);
	wattroff(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_BOLD | A_REVERSE);
}

int	draw_score(t_game *game, int start_y, int start_x)
{
	char *output[2];
	int	shift_left = 0;
	int y = 0;

	game->max_score = read_best_score();
	output[0] = "SCORE: ";
	output[1] = "BEST: ";
	wattron(game->main_w, COLOR_PAIR(7) | A_BOLD ); //A_ITALIC
	shift_left = intlen(game->score) + 5;
	mvwprintw(game->main_w, start_y + y, start_x - shift_left, "%d", game->score);
	mvwprintw(game->main_w, start_y + y, start_x - shift_left - (int)ft_strlen(output[y]), "%s", output[y]);
	y += 1;
	shift_left = intlen(game->max_score) + 5;
	mvwprintw(game->main_w, start_y + y, start_x - shift_left, "%d", game->max_score);
	mvwprintw(game->main_w, start_y + y, start_x - shift_left - (int)ft_strlen(output[y]), "%s", output[y]);
	wattroff(game->main_w, COLOR_PAIR(7) | A_BOLD); //A_ITALIC
	return (y + 1);
}

