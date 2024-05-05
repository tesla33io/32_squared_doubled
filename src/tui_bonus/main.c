#include "../../inc/tui_bonus.h"

int		game_loop(t_game *game);
void	start_game(int sig);
void	game_init(t_game *game);
int		get_box_width(int win_x);

void	draw_rectangle(WINDOW *win, int row, int col, int width, int value);
void	draw_cell(WINDOW *win, int row, int col, int width, int value);
void	draw_value(WINDOW *win, int row, int col, int value);

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
	if (value == 0)
		return (0);
	while (result < value)
	{
		result *= 2;
		i++;
	}
	return (i);
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
	init_color(CUSTOM_COLORS_START + 1, 238, 28, 218);
	init_pair(CUSTOM_COLORS_START + 1, CUSTOM_COLORS_START + 1, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 2, 207, 224, 200);
	init_pair(CUSTOM_COLORS_START + 2, CUSTOM_COLORS_START + 2, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 3, 242, 177, 121);
	init_pair(CUSTOM_COLORS_START + 3, CUSTOM_COLORS_START + 3, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 4, 245, 149, 199);
	init_pair(CUSTOM_COLORS_START + 4, CUSTOM_COLORS_START + 4, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 5, 246, 124, 95);
	init_pair(CUSTOM_COLORS_START + 5, CUSTOM_COLORS_START + 5, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 6, 246, 194, 59);
	init_pair(CUSTOM_COLORS_START + 6, CUSTOM_COLORS_START + 6, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 7, 237, 207, 114);
	init_pair(CUSTOM_COLORS_START + 7, CUSTOM_COLORS_START + 7, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 8, 237, 204, 197);
	init_pair(CUSTOM_COLORS_START + 8, CUSTOM_COLORS_START + 8, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 9, 237, 200, 80);
	init_pair(CUSTOM_COLORS_START + 9, CUSTOM_COLORS_START + 9, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 10, 237, 197, 63);
	init_pair(CUSTOM_COLORS_START + 10, CUSTOM_COLORS_START + 10, COLOR_BLACK);
	init_color(CUSTOM_COLORS_START + 11, 237, 194, 46);
	init_pair(CUSTOM_COLORS_START + 11, CUSTOM_COLORS_START + 11, COLOR_BLACK);
}


int	init_colors(t_game *game)
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
	if (is_power_two(WIN_VALUE) == 1)
		game->win_value = WIN_VALUE;
	else
		game->win_value = 0;
	return (0);
}

void	win_resize(t_game *game)
{
	// if (g_sig != 28)
		// retuwrn ;
	int new_height, new_width, term_y, term_x = 0;
	// werase(game->main_w);
	// clear();

	getmaxyx(game->main_w, new_height, new_width);
	wresize(game->main_w, new_height, new_width);
	// redrawwin(game->main_w);
	// WINDOW *temp_w = newwin(new_height, new_width, 0, 0);
	// copywin(game->main_w, temp_w, 0, 0, 0, 0, new_height - 1, new_width - 1, TRUE);
	// delwin(game->main_w);

	// endwin(); //end terminal
	// terminal_start();
	getmaxyx(stdscr, term_y, term_x);
	game->y_max = term_y - 1;
	game->x_max = term_x - 1;
	// game->main_w = newwin(term_y, term_x, 0, 0);
	// copywin(temp_w, game->main_w, 0, 0, 0, 0, term_y - 1, term_x - 1, TRUE);
	// delwin(temp_w);
	// refresh();
	// doupdate();
	wrefresh(game->main_w);
	game_loop(game);
}

// void	draw_in_middle(t_game *game, )

int	menu_init(t_game *game)
{
	char *titel[4];
	int ch, higlight, x_start, y_start, width, win_state, shift, w_x, w_y = 0;

	titel[0] = "Join the Numbers: Reach";
	titel[1] = "Choose your grid size";
	titel[2] = "  4x4  ";
	titel[3] = "  5x5  ";
	higlight = 4;
	game->grid = 0;
	win_state = game->win_value;
	while (1)
	{
		wclear(game->main_w);
		wattron(game->main_w, A_BOLD);
		width = get_box_width(game->x_max);
		y_start = game->y_max / 2 - width / 2 + width / 5;
		x_start = game->x_max / 2 - width / 2;
		draw_cell(game->main_w, y_start, x_start, width, 8);
		shift = width / 6;
		mvwprintw(game->main_w, y_start + shift, x_start + shift * 0.9, "%s", titel[0]);
		if (win_state == 0)
			win_state = 2048;
		wattron(game->main_w, COLOR_PAIR(6) | A_BOLD | A_BLINK | A_DIM);
		mvwprintw(game->main_w, y_start + shift, x_start + shift * 0.9 + (int)strlen(titel[0]) + 2, "%i", win_state);
		wattroff(game->main_w, COLOR_PAIR(6) | A_BOLD | A_BLINK | A_DIM);
		mvwprintw(game->main_w, y_start + shift * 1.5, x_start + shift * 1.7, "%s", titel[1]);
		if (higlight == 4)
			wattron(game->main_w, A_REVERSE);
		mvwprintw(game->main_w, y_start + shift * 2.4, x_start + width * 0.2, "%s", titel[2]);
		wattroff(game->main_w, A_REVERSE);
		if (higlight == 5)
			wattron(game->main_w, A_REVERSE);
		mvwprintw(game->main_w, y_start + shift * 2.4, x_start + width * 0.6, "%s", titel[3]);
		wattroff(game->main_w, A_REVERSE);
		wattroff(game->main_w, A_BOLD);
		wrefresh(game->main_w);
		ch = wgetch(game->main_w);
		// if (g_sig == 28)
		// {
		// 	g_sig = 0;
		// 	win_resize(game);
		// }
		if (ch == 10)
		{
			game->grid = higlight;
			break ;
		}
		if (ch == 27)
		{
			delwin(game->main_w);
			endwin();
			return (1);
		}
		switch (ch)
		{
			case KEY_RIGHT:
				higlight = 5;
				break;
			case KEY_LEFT:
				higlight = 4;
				break;
			default:
				break;
		}
	}
	return (0);
}

void	print_board(int board[MAX_SIZE][MAX_SIZE])
{
	printf("\n\n");
	for (int i=0; i < 5; i++)
	{
		for (int j=0; j < 5; j++)
		{
			printf("%i  ", board[i][j]);
		}
		printf("\n\n");
	}
}

/* 
void	replace_empty_cells(t_game *game)
{
	int	size = game->grid;
	int col, row = 0;
	if (game->dir == 'u')
	{
		row = 1;
		while (col < size)
		{
			while (row < size)
			{
				if (game->board[row - 1][col] == 0)
				{
					game->board[row - 1][col] = game->board[row][col];
					game->board[row][col] = 0;
				}
				row++;
			}
			col++;
		}
	}
	else if (game->dir == 'd')
	{
		for (int col = size - 1; col >= 0; col--)
		{
			for (int row = size - 1; row >= 0; row--)
			{
				if (game->board[row][col] == 0 && game->board[row - 1][col])
				{
					game->board[row][col] = game->board[row - 1][col];
					game->board[row - 1][col] = 0;
				}
			}
		}
	}
}
*/

/*

┓┏┓┏┓┏┓┏━┏┓━┓┏┓┏┓┏┓
┃┏┛ ┫┃┃┗┓┣┓ ┃┣┫┗┫┃┫
┻┗━┗┛┗╋┗┛┗┛ ╹┗┛┗┛┗┛

┏┓┏┓┏┓┳┓┏┓
┗┓┃ ┃┃┣┫┣ 
┗┛┗┛┗┛┛┗┗┛

┳┓┏┓┏┓┏┳┓
┣┫┣ ┗┓ ┃ 
┻┛┗┛┗┛ ┻           


╔═╗╔═╗╔═╗╦═╗╔═╗
╚═╗║  ║ ║╠╦╝║╣
╚═╝╚═╝╚═╝╩╚═╚═╝

┌─┐┌─┐┌─┐┬─┐┌─┐
└─┐│  │ │├┬┘├┤ 
└─┘└─┘└─┘┴└─└─┘

╔╗ ╔═╗╔═╗╔╦╗
╠╩╗║╣ ╚═╗ ║ 
╚═╝╚═╝╚═╝ ╩ 

╔═╗   ╦ ╦  ╔═╗  ╦═╗  ╔╦╗  ╦ ╦  ╦ ╦  ╦  ╔═╗  ╔═╗  ╔═╗  ╔═╗  ╔╦╗  ╔═╗  ╔═╗  ╦ ╦   ╦  ╦╔═  ╦    ╔═╗  ═╗ ╦  ╔═╗  ╦  ╦  ╔╗   ╔╗╔  ╔╦╗
║═╬╗  ║║║  ║╣   ╠╦╝   ║   ╚╦╝  ║ ║  ║  ║ ║  ╠═╝  ╠═╣  ╚═╗   ║║  ╠╣   ║ ╦  ╠═╣   ║  ╠╩╗  ║    ╔═╝  ╔╩╦╝  ║    ╚╗╔╝  ╠╩╗  ║║║  ║║║
╚═╝╚  ╚╩╝  ╚═╝  ╩╚═   ╩    ╩   ╚═╝  ╩  ╚═╝  ╩    ╩ ╩  ╚═╝  ═╩╝  ╚    ╚═╝  ╩ ╩  ╚╝  ╩ ╩  ╩═╝  ╚═╝  ╩ ╚═  ╚═╝   ╚╝   ╚═╝  ╝╚╝  ╩ ╩

*/

int	draw_score(t_game *game, int start_y, int start_x)
{
	char *output[2];

	// output[0] = "┏┓┏┓┏┓┳┓┏┓";
	// output[1] = "┗┓┃ ┃┃┣┫┣ ";
	// output[2] = "┗┛┗┛┗┛┛┗┗┛";
	// output[3] = "┳┓┏┓┏┓┏┳┓";
	// output[4] = "┣┫┣ ┗┓ ┃ ";
	// output[5] = "┻┛┗┛┗┛ ┻ ";
	output[0] = "SCORE: ";
	// output[1] = "SCORE";
	// output[2] = "SCORE";
	output[1] = "BEST: ";
	// output[4] = "BEST";
	// output[5] = "BEST";
	wattron(game->main_w, COLOR_PAIR(7) | A_BOLD | A_ITALIC);
	// for (int i = 0; i < 3; i++)
	// {
	// 	mvwaddch(game->main_w, start_y, start_x, output[i]);
	// 	start_y++;
	// }
	int y = 0;
	mvwprintw(game->main_w, start_y + y, start_x, "%s", output[y]);
	mvwprintw(game->main_w, start_y + y, start_x + (int)strlen(output[y]), "%d", game->score);
	y++;
	mvwprintw(game->main_w, start_y + y, start_x, "%s", output[y]);
	mvwprintw(game->main_w, start_y + y, start_x + (int)strlen(output[y]), "%d", game->max_score);
	wattroff(game->main_w, COLOR_PAIR(7) | A_BOLD | A_ITALIC);
	return (y + 1);
}


// int mvwhline(WINDOW *, int y, int x, chtype ch, int n);
// int mvwvline(WINDOW *, int y, int x, chtype ch, int n);
void	draw_cell(WINDOW *win, int row, int col, int width, int value)
{
	// https://de.wikibooks.org/wiki/Ncurses:_Fenster
	int	power;

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
	int y, x = 0;
	int	power = get_power(value);

	wattron(win, COLOR_PAIR(CUSTOM_COLORS_START + power) | A_REVERSE);
	for (y = row + 1; y < row + width - 5; y++) {
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

	// wattron(win, COLOR_WHITE | A_BOLD);
	mvwprintw(win, row, col, "%i", value);
	// wattroff(win, COLOR_WHITE | A_BOLD);
}

void	draw_grid(t_game *game, int y, int x, int width)
{
	int	size = game->grid;
	int	row, col = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			draw_cell(game->main_w, y + (row * width / 2), x + (col * width), width, 0);
			draw_rectangle(game->main_w, y + (row * width / 2), x + (col * width), width, game->board[row][col]);
			draw_value(game->main_w, y + (row * width / 2) + width / 4, x + col * width + (width / 2), game->board[row][col]);
			col++;
		}
		row++;
	}
}

void	grid(t_game *game)
{
	werase(game->main_w);
	int	size = game->grid;
	int	row, col, start_x, start_y, width, shift;
	getmaxyx(game->main_w, row, col);
	// wprintw(game->main_w, "row: %d, col: %d", row, col);
	width = 10;
	// shift = (col - width * size) / 2;
	if ((width % 2) != 0)
		width -= width % 2;
	int y = draw_score(game, 1, 1);
	draw_grid(game, 1 + y + 1, 1, width);
	wrefresh(game->main_w);
}

void	draw_board(t_game *game, int board[MAX_SIZE][MAX_SIZE])
{
	int	size = game->grid;
	werase(game->main_w);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			mvwprintw(game->main_w, i, j * 5, "%4d", board[i][j]);
	}
	wrefresh(game->main_w);
}

int	is_movement(t_game *game)
{
	int	size = game->grid;
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
	int	size = game->grid;

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
		return (1); //no emply cells
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

int	loser_wnd(t_game *game, WINDOW *win)
{
	char *titel[3];
	int ch, x_start, y_start, width, win_state, shift, w_x, w_y = 0;

	titel[0] = "Game over!";
	titel[1] = "ENTER: Start again";
	titel[2] = "ESCAPE: Quit the game";
	keypad(win, TRUE);
	while (1)
	{
		werase(win);
		width = get_box_width(game->x_max);
		// x_start = get_midle();
		wrefresh(win);
		ch = wgetch(win);
		if (ch == 10)
		{
			game->menu = true;
			return (start_game(28), 0);
		}
		else if (ch == 27)
			return (endwin(), 1);
		
	}
	return (0);
}

int	moves(t_game *game, char dir)
{
	if (dir == '0')
		return (1);
	update_board(game->board, game->grid, game->dir);
	if (set_random_nbr(game, get_random_nbr()) != 0) // && is_movement(game) != 0 // no possible moements
	{
		start_game(28);
		// if (loser_wnd(game, game->main_w) != 0)
		// 	return (1);
	}
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
		int ch = wgetch(game->main_w);
		// if (g_sig == 28)
		// {
		// 	g_sig = 0;
		// 	win_resize(game);
		// 	return ;
		// }
		if (ch == 27)
		{
			delwin(game->main_w);
			endwin();
			// refresh();
			return ;
		}
		switch (ch)
		{
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
			free(game->board);
			endwin();
			return ;
		}
		for (int j = 0; j < size; j++) {
			game->board[i][j] = 0;
		}
	}
	game->score = 0;
	game->max_score = 0;
	set_random_nbr(game, 2);
	set_random_nbr(game, 2);
	grid(game);
}

// Signal handler for SIGWINCH (window resize)
void handle_sigwinch(int sig) //sig == 28
{
	g_sig = sig;
}

void	handle_sigint(int sig) /// sig == 2
{
	clear();
	// system("/bin/zsh");
	endwin();
	system("/bin/zsh");
	g_sig = sig;
	signal(SIGINT, SIG_DFL);
	// write(1, "\n", 1);
	// reset_prog_mode();
}

int	game_loop(t_game *game)
{
	keypad(game->main_w, true);
	keypad(stdscr, true);
	mousemask(0, NULL);
	getmaxyx(stdscr, game->y_max, game->x_max);
	if (game->x_max < 75 || game->y_max < 25)
	{
		clear();
		printw("y:%d x:%d", game->y_max, game->x_max);
		// printw("Warning: terminal too small, please either resize your terminal or press ESCAPE to quit");
		refresh();
		while (1)
		{
			int ch = getch();
			// if (ch == KEY_RESIZE)
			// {
			// 	g_sig = 0;
			// 	win_resize(game);
			// 	break ;
			// }
			if (ch == 27)
			{
				endwin();
				return (2);
			}
		}
	}
	if (game->menu)
	{
		if (menu_init(game) != 0)
			return (1);
	}
	srand(time(NULL));
	new_game(game);
	return (0);
}

void	start_game(int sig)
{
	if (sig != SIGWINCH)
		return ;
	static t_game	game;
	// win_resize(&game);
	// def_shell_mode(); // def_prog_mode()
	if (win_init(&game) != 0)
		return ;
	if (init_colors(&game) != 0)
		return ;
	game_loop(&game);
	return ;
}

int	main (void)
{
	signal(SIGWINCH, handle_sigint);
	// signal(SIGINT, handle_sigint);
	start_game(SIGWINCH);
	return (0);
}
