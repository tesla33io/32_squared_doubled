#include "../../inc/tui_bonus.h"

int	loser_wnd(t_game *game)
{
	char *titel[3];
	int ch, x_start, y_start, width = 0;

	titel[0] = "GAME OVER!";
	titel[1] = "ENTER: Start again";
	titel[2] = "ESCAPE: Quit the game";
	keypad(game->main_w, TRUE);
	while (1)
	{
		wclear(game->main_w);
		getmaxyx(game->main_w, game->y_max, game->x_max);
		if (game->y_max < 24 || game->x_max < 54)
		{
			for (int i = 0; i < (int)(sizeof(titel) / sizeof(char *)); i++)
				mvwprintw(game->main_w, i + 1, 1, "%s", titel[i]);
		}
		else
		{
			width = get_box_width(game->x_max);
			y_start = game->y_max / 2 - width / 2 + width / 5;
			x_start = game->x_max / 2 - width / 2;
			draw_cell(game->main_w, y_start, x_start, width, 64);
			for (int i = 0; i < (int)(sizeof(titel) / sizeof(char *)); i++)
				mvwprintw(game->main_w, i * 3 + y_start + width * 0.19, x_start + width * 0.5 - (int)ft_strlen(titel[i]) / 2, "%s", titel[i]);
		}
		wrefresh(game->main_w);
		ch = wgetch(game->main_w);
		if (ch == KEY_RESIZE)
			continue;
		else if (ch == 10)
		{
			game->menu = true;
			return (game_loop(game), 0);
		}
		else if (ch == 27)
		{
			endwin();
			if (game->board)
				destroy_board(game->board, game->grid);
			return (1);
		}
	}
	return (0);
}

int	winer_wnd(t_game *game)
{
	char *titel[4];
	int ch, x_start, y_start, width, higlight = 0;

	titel[0] = "YOU WIN!";
	titel[1] = "Keep going";
	titel[2] = "Start again";
	titel[3] = "*press ESCAPE to quit the game";
	keypad(game->main_w, TRUE);
	higlight = 1;
	while (1)
	{
		wclear(game->main_w);
		getmaxyx(game->main_w, game->y_max, game->x_max);
		if (game->y_max < 24 || game->x_max < 54)
		{
			for (int i = 0; i < (int)(sizeof(titel) / sizeof(char *)); i++)
			{
				if (i == higlight)
					wattron(game->main_w, A_REVERSE);
				mvwprintw(game->main_w, i + 2, 2, "%s", titel[i]);
				wattroff(game->main_w, A_REVERSE);
			}
		}
		else
		{
			width = get_box_width(game->x_max);
			y_start = game->y_max / 2 - width / 2 + width / 5;
			x_start = game->x_max / 2 - width / 2;
			draw_cell(game->main_w, y_start, x_start, width, 4);
			for (int i = 0; i < (int)(sizeof(titel) / sizeof(char *)); i++)
			{
				if (i == higlight)
					wattron(game->main_w, A_REVERSE);
				mvwprintw(game->main_w, i * 3 + y_start + width * 0.19, x_start + width * 0.5 - (int)ft_strlen(titel[i]) / 2, "%s", titel[i]);
				wattroff(game->main_w, A_REVERSE);
			}
		}
		wrefresh(game->main_w);
		ch = wgetch(game->main_w);
		if (ch == KEY_RESIZE)
			continue;
		if (ch == 10)
		{
			if (higlight == 1)
			{
				game->win_value = 0;
				return (0);
			}
			if (higlight == 2)
			{
				game->menu = true;
				game_loop(game);
				return (1);
			}
		}
		else if (ch == 27)
		{
			endwin();
			if (game->board)
				destroy_board(game->board, game->grid);
			return (1);
		}
		else if (ch == KEY_UP)
		{
			higlight = 1;
			continue;
		}
		else if (ch == KEY_DOWN)
		{
			higlight = 2;
			continue;
		}
	}
	return (0);
}


int	menu_init(t_game *game)
{
	char *titel[4];
	int ch = 0;
	int higlight = 0;
	int x_start = 0;
	int y_start = 0;
	int width = 0;
	int win_state = 0;
	int shift = 0;

	titel[0] = "Join the Numbers: Reach";
	titel[1] = "Choose your grid size";
	titel[2] = "  4x4  ";
	titel[3] = "  5x5  ";
	higlight = 4;
	game->grid = 0;
	if (is_power_two(WIN_VALUE) == 1)
		game->win_value = WIN_VALUE;
	else
		game->win_value = 0;
	win_state = game->win_value;
	while (1)
	{
		wclear(game->main_w);
		wattron(game->main_w, A_BOLD);
		getmaxyx(game->main_w, game->y_max, game->x_max);
		if (game->y_max < 24 || game->x_max < 54)
		{
			mvwprintw(game->main_w, 1, 1, "%s", titel[0]);
			if (win_state == 0)
				win_state = 2048;
			mvwprintw(game->main_w, 1, (int)strlen(titel[0]) + 2, "%i", win_state);
			mvwprintw(game->main_w, 2, 1, "%s", titel[1]);
			if (higlight == 4)
				wattron(game->main_w, A_REVERSE);
			mvwprintw(game->main_w, 3, 1, "%s", titel[2]);
			wattroff(game->main_w, A_REVERSE);
			if (higlight == 5)
				wattron(game->main_w, A_REVERSE);
			mvwprintw(game->main_w, 3, ft_strlen(titel[2]) + 1, "%s", titel[3]);
			wattroff(game->main_w, A_REVERSE);
		}
		else{
			width = get_box_width(game->x_max);
			y_start = game->y_max / 2 - width / 2 + width / 5;
			x_start = game->x_max / 2 - width / 2;
			draw_cell(game->main_w, y_start, x_start, width, 64);
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
		}
		wrefresh(game->main_w);
		ch = wgetch(game->main_w);
		if (ch == 10)
		{
			game->grid = higlight;
			break ;
		}
		if (ch == 27)
		{
			endwin();
			if (game->board)
				destroy_board(game->board, game->grid);
			return (1);
		}
		switch (ch)
		{
			case KEY_RESIZE:
				break;
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

int	intlen(int value)
{
	int	n = 0;

	while (value > 0)
	{
		value /= 10;
		n++;
	}
	return (n);
}

void	grid(t_game *game)
{
	int	size = game->grid;
	int	start_x, start_y, width, tmp_x;

	wclear(game->main_w);
	getmaxyx(game->main_w, game->y_max, game->x_max);
	if (game->y_max < 24 || game->x_max < 54)
	{
		wclear(game->main_w);
		wprintw(game->main_w, "Warning: terminal too small, please either resize your terminal or press ESCAPE to quit");
		return ;
	}
	tmp_x = game->x_max;
	if (tmp_x > 105)
		tmp_x = 104;
	width = (tmp_x - 1) / (size + 2);
	if ((width * (size + 2)) >= (game->x_max) || (width * (size + 2)) >= (game->y_max))
		width = game->y_max / size + 2;
	if ((width % 2) != 0)
		width -= width % 2;
	start_x = (game->x_max - 1) / 2 - ((width * size) / 2);
	start_y = (game->y_max - 1) / 2 - ((width * size) / 4);
	int i = draw_score(game, start_y, start_x + (width * size));
	draw_grid(game, start_y + i + 1, start_x, width);
	wrefresh(game->main_w);
}
