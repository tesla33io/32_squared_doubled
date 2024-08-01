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
			draw_border(game->main_w, y_start, x_start, width, COLOR_BLACK);
			for (int i = 0; i < (int)(sizeof(titel) / sizeof(char *)); i++)
				mvwprintw(game->main_w, i * 3 + y_start + width * 0.19, x_start + width * 0.5 - (int)ft_strlen(titel[i]) / 2,
				 "%s", titel[i]);
		}
		wrefresh(game->main_w);
		ch = wgetch(game->main_w);
		if (ch == KEY_RESIZE)
			continue;
		else if (ch == 10)
		{
			game->menu = true;
			launch_game(game);
			return (1);
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
			draw_border(game->main_w, y_start, x_start, width, COLOR_BLACK);
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
				launch_game(game);
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
