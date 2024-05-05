#include "../../inc/tui_bonus.h"
#include <ncurses.h>
#include <unistd.h>


static int	read_best_score(void);
static void	save_best_score(int best);

int	g_sig = 0;

int	is_power_two(int value)
{
	if (value <= 0)
		return (0);
	return ((value & (value - 1)) == 0);
}

int	get_power(int value)
{
	int result = 1;
	int i = 0;
	if (value <= 0 || value > 2048)
		return (0);
	while (result < value)
	{
		result *= 2;
		i++;
	}
	return (i);
}

void	destroy_board(int **brd, int size)
{
	for (int y = 0; y < size; y++)
		ft_free_ptr(brd[y]);
	ft_free_ptr(brd);
}


void	setup_color_pairs(void)
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 0, 249, 246, 242);
	init_pair(CUSTOM_COLORS_START + 0, CUSTOM_COLORS_START + 0, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 1, 255, 190, 99);
	init_pair(CUSTOM_COLORS_START + 1, CUSTOM_COLORS_START + 1, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 2, 245, 92, 37);
	init_pair(CUSTOM_COLORS_START + 2, CUSTOM_COLORS_START + 2, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 3, 115, 122, 255);
	init_pair(CUSTOM_COLORS_START + 3, CUSTOM_COLORS_START + 3, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 4, 145, 48, 209);
	init_pair(CUSTOM_COLORS_START + 4, CUSTOM_COLORS_START + 4, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 5, 118, 209, 100);
	init_pair(CUSTOM_COLORS_START + 5, CUSTOM_COLORS_START + 5, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 6, 57, 11, 112);
	init_pair(CUSTOM_COLORS_START + 6, CUSTOM_COLORS_START + 6, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 7, 209, 54, 54);
	init_pair(CUSTOM_COLORS_START + 7, CUSTOM_COLORS_START + 7, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 8, 108, 213, 217);
	init_pair(CUSTOM_COLORS_START + 8, CUSTOM_COLORS_START + 8, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 9, 193, 149, 237);
	init_pair(CUSTOM_COLORS_START + 9, CUSTOM_COLORS_START + 9, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 10, 245, 110, 240);
	init_pair(CUSTOM_COLORS_START + 10, CUSTOM_COLORS_START + 10, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 11, 237, 133, 69);
	init_pair(CUSTOM_COLORS_START + 11, CUSTOM_COLORS_START + 11, COLOR_BLACK);
}


int	init_colors(void)
{
	if (has_colors() == FALSE)
	{
		printf("Your terminal does not support color\n");
		endwin();
		return (-1);
	}
	start_color();
	setup_color_pairs();
	return (0);
}

void	terminal_start(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	mousemask(0, NULL);
	refresh();
}

int	win_init(t_game *game)
{
	if (g_sig == 28)
		return (0);
	terminal_start();
	getmaxyx(stdscr, game->y_max, game->x_max);
	game->menu = true;
	game->main_w = newwin(game->y_max, game->x_max, 0, 0);
	return (0);
}

int	draw_score(t_game *game, int start_y, int start_x)
{
	char *output[2];
	int	shift_left = 0;
	int y = 0;

	game->max_score = read_best_score();
	output[0] = "SCORE: ";
	output[1] = "BEST: ";
	wattron(game->main_w, COLOR_PAIR(7) | A_BOLD | A_ITALIC);
	shift_left = intlen(game->score) + 5;
	mvwprintw(game->main_w, start_y + y, start_x - shift_left, "%d", game->score);
	mvwprintw(game->main_w, start_y + y, start_x - shift_left - (int)ft_strlen(output[y]), "%s", output[y]);
	y += 1;
	shift_left = intlen(game->max_score) + 5;
	mvwprintw(game->main_w, start_y + y, start_x - shift_left, "%d", game->max_score);
	mvwprintw(game->main_w, start_y + y, start_x - shift_left - (int)ft_strlen(output[y]), "%s", output[y]);
	wattroff(game->main_w, COLOR_PAIR(7) | A_BOLD | A_ITALIC);
	return (y + 1);
}

void	draw_cell(WINDOW *win, int row, int col, int width, int value)
{
	int	power = 0;

	if (value <= 0)
		power = value;
	else
		power = get_power(value);
	wattron(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_BOLD);
	mvwhline(win, row, col, ACS_HLINE, width);
	mvwhline(win, row + width / 2, col, ACS_HLINE, width);
	mvwvline(win, row, col, ACS_VLINE, width / 2);
	mvwvline(win, row, col + width, ACS_VLINE, width / 2 + 1);
	mvwaddch(win, row, col, ACS_PLUS);
	mvwaddch(win, row + width / 2, col, ACS_PLUS);
	mvwaddch(win, row + width / 2, col + width, ACS_PLUS);
	mvwaddch(win, row, col + width, ACS_PLUS);
	wattroff(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_BOLD);
}

void	draw_rectangle(WINDOW *win, int row, int col, int width, int value)
{
	int y = 0;
	int x = 0;
	int	power = get_power(value);

	wattron(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_REVERSE);
	for (y = row + 1; y < row + width - (width / 2); y++) {
		for (x = col + 2; x < col + width - 1; x++) {
			mvwaddch(win, y, x, ' ');
		}
	}
	wattroff(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_REVERSE);
}

void	draw_value(WINDOW *win, int row, int col, int value)
{
	if (value <= 0)
		return ;

	mvwprintw(win, row, col, "%i", value);
}

void	draw_grid(t_game *game, int y, int x, int width)
{
	int	size = game->grid;
	int	row = 0;
	int col = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			draw_cell(game->main_w, y + (row * width / 2), x + (col * width), width, 0);
			draw_rectangle(game->main_w, y + (row * width / 2), x + (col * width), width, game->board[row][col]);
			draw_value(game->main_w, y + (row * width / 2) + width / 4, x + col * width + (width / 2) - intlen(game->board[row][col]) / 2, game->board[row][col]);
			col++;
		}
		row++;
	}
}


int	is_movement(t_game *game)
{
	int	size = 0;
	size = game->grid;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (game->board[i][j + 1] && game->board[i + 1][j] && (game->board[i][j] == game->board[i + 1][j] || game->board[i][j] == game->board[i][j + 1]))
				return (0);
		}
	}
	return (1);
}

int get_random_nbr(void)
{
	int	nbr = rand() % 100;
	if (nbr < 90)
		return (2);
	else
		return (4);
}

int	set_random_nbr(t_game *game, int nbr)
{
	int	empty_cells[MAX_SIZE * MAX_SIZE][2];
	int	i = 0;
	int	size = 0;
	size = game->grid;

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (game->board[row][col] == 0)
			{
				i++;
				empty_cells[i - 1][0] = row;
				empty_cells[i - 1][1] = col;
			}
		}
	}
	if (i == 0)
		return (1);
	int n = rand() % i;
	int r = empty_cells[n][0];
	int c = empty_cells[n][1];
	game->board[r][c] = nbr;
	return (0);
}

int	get_box_width(int win_x)
{
	int w_x = win_x - 1;
	if (w_x > 105)
		w_x = 104;
	return (w_x * 0.5);
}


static int	read_best_score(void)
{
	int	fbest = open(FBEST, O_RDONLY);
	if (fbest < 0)
		return (-1);
	char	score_text[17];
	int		score_val;
	int		bytes_read = -1;
	bytes_read = read(fbest, score_text, 16);
	if (bytes_read < 0)
		return (-1);
	score_text[bytes_read] = 0;
	score_val = ft_atoi(score_text);
	close(fbest);
	return (score_val);
}

static void	save_best_score(int best)
{
	int	fbest = open(FBEST, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fbest < 0)
		return ;
	char	*bscore_str = ft_itoa(best);
	if (!bscore_str)
		return ;
	write(fbest, bscore_str, ft_strlen(bscore_str));
	ft_free_ptr(bscore_str);
}

int	moves(t_game *game, char dir)
{
	if (dir == '0')
		return (1);

	if (!moves_left(game->board, game->grid, 'l')
		&& !moves_left(game->board, game->grid, 'r') && !moves_left(game->board, game->grid, 'u')
		&& !moves_left(game->board, game->grid, 'd') )
	{
		if (loser_wnd(game) != 0)
			return (-1);
	}
	if (!moves_left(game->board, game->grid, dir))
		return (0);

	game->max_score = read_best_score();

	game->score += update_board(game->board, game->grid, game->dir);

	if (game->score > game->max_score)
		save_best_score(game->score);

	if (has_win_condition(game->board, game->grid, game->win_value))
	{
		if (winer_wnd(game) != 0)
			return (-1);
	}
	set_random_nbr(game, get_random_nbr());
	grid(game);
	return (0);
}

void	new_game(t_game *game)
{
	if (game->menu)
		game_init(game);
	game->menu = false;
	game->dir = '0';
	while (1)
	{
		grid(game);
		int ch = wgetch(game->main_w);
		if (ch == 27)
		{
			endwin();
			if (game->board)
				destroy_board(game->board, game->grid);
			return ;
		}
		switch (ch)
		{
			case KEY_RESIZE:
				break;
			case KEY_UP:
				game->dir = 'u';
				break;
			case KEY_DOWN:
				game->dir = 'd';
				break;
			case KEY_LEFT:
				game->dir = 'l';
				break;
			case KEY_RIGHT:
				game->dir = 'r';
				break;
			default:
				game->dir = '0';
				break;
		}
		if (moves(game, game->dir) == -1)
			return ;
	}
}

void	game_init(t_game *game)
{
	int size = game->grid;
	if (game->board)
		destroy_board(game->board, game->grid);
	game->board = ft_malloc(NULL, sizeof(int *) * size);
	if (!game->board)
	{
		endwin();
		return ;
	}
	for (int i = 0; i < size; i++) {
		game->board[i] = ft_malloc(NULL, sizeof(int) * size);
		if (!game->board[i])
		{
			ft_free_ptr(game->board);
			endwin();
			return ;
		}
		for (int j = 0; j < size; j++) {
			game->board[i][j] = 0;
		}
	}
	if (is_power_two(WIN_VALUE) == 1)
		game->win_value = WIN_VALUE;
	else
		game->win_value = 0;
	game->score = 0;
	game->max_score = 0;
	set_random_nbr(game, 2);
	set_random_nbr(game, 2);
	grid(game);
}

int	game_loop(t_game *game)
{
	keypad(game->main_w, true);
	keypad(stdscr, true);
	mousemask(0, NULL);
	getmaxyx(game->main_w, game->y_max, game->x_max);
	if (game->menu)
	{
		if (menu_init(game) != 0)
			return (1);
	}
	srand(time(NULL));
	new_game(game);
	return (0);
}

int	main (void)
{
	t_game	game;

	if (win_init(&game) != 0)
		return (1);
	if (init_colors() != 0)
		return (1);
	game.board = NULL;
	game_loop(&game);
	return (0);
}
