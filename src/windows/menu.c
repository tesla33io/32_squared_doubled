#include "../../inc/game.h"
#include "../../inc/tui_bonus.h"
#include "../../inc/titles.h"
#include "../../lib/libft/libft.h"

void	displayBoardSelection(t_game *game, int y_margin, int maxWidth, int higlight);

int	menu_init(t_game *game)
{
	char *titel[5];
	int ch = 0;
	int higlight = 0;
	int x_start = 0;
	int top_margin = 0;

	titel[0] = "W E L C O M E  T O  P U Z Z L E";
	titel[1] = "R E A C H    ";
	higlight = GRID_SIZE_4;
	game->grid = 0;
	if (is_power_two(WIN_VALUE) == 1)
		game->win_value = WIN_VALUE;
	else
		game->win_value = 0;
	int winer_state = (game->win_value == 0) ? 2048 : game->win_value;
	while (1)
	{
		if (game->y_max < 45 && game->x_max < 80)
			top_margin = 3;
		else if (game->y_max <= 43 || game->x_max <= 80)
			top_margin = 0;
		else
			top_margin = 3;
		int y_margin = top_margin;
		wclear(game->main_w);
		wattron(game->main_w, A_BOLD);
		getmaxyx(game->main_w, game->y_max, game->x_max);
		displayGameTitle(game->main_w, TITLE_SMALL, game->x_max, y_margin);
		y_margin += getArrSize(titles[TITLE_SMALL].titleText);
		y_margin += top_margin;
		displayCenteredMsg(game->main_w, y_margin, game->x_max, titel[0]);
		y_margin = y_margin + top_margin + 1;
		displayCenteredMsg(game->main_w, y_margin, game->x_max, titel[1]);
		wattron(game->main_w, COLOR_PAIR(6) | A_BOLD | A_BLINK | A_DIM);
		x_start = getHalfWidth(game->x_max, ft_strlen(titel[1]));
		mvwprintw(game->main_w, y_margin, x_start + (int)ft_strlen(titel[1]), "%i", winer_state);
		y_margin = y_margin + top_margin + 1;
		wattroff(game->main_w, COLOR_PAIR(6) | A_BOLD | A_BLINK | A_DIM);
		displayBoardSelection(game, y_margin, game->x_max, higlight);
		wattroff(game->main_w, A_BOLD);
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
				higlight = GRID_SIZE_5;
				break;
			case KEY_LEFT:
				higlight = GRID_SIZE_4;
				break;
			default:
				break;
		}
	}
	return (0);
}

void	displayGridSelection(WINDOW *win, int y_margin, int maxWidth, int higlight)
{
	char *msg = "C H O O S E  G R I D  S I Z E";
	mvwprintw(win, y_margin, getHalfWidth(maxWidth, ft_strlen(msg)), "%s", msg);
	y_margin += 2;
	if (higlight != GRID_SIZE_4 && higlight != GRID_SIZE_5)
		return ;
	int x_start = getHalfWidth(maxWidth, 2) - ft_strlen(" [ 4 x 4 ] ");
	if (higlight == GRID_SIZE_4)
		wattron(win, A_REVERSE);
	mvwprintw(win, y_margin, x_start, "%s", " [ 4 x 4 ] ");
	wattroff(win, A_REVERSE);
	if (higlight == GRID_SIZE_5)
		wattron(win, A_REVERSE);
	x_start = x_start + ft_strlen(" [ 4 x 4 ] ") + 4;
	mvwprintw(win, y_margin, x_start, "%s", " [ 5 x 5 ] ");
	wattroff(win, A_REVERSE);
}

void	displayBoardSelection(t_game *game, int y_margin, int maxWidth, int higlight)
{
	if (higlight != GRID_SIZE_4 && higlight != GRID_SIZE_5)
		return ;
	int margin = (maxWidth <= 82) ? 4 : 6;
	if (maxWidth < 80 && game->y_max < 45)
	{
		displayGridSelection(game->main_w, y_margin, maxWidth, higlight);
		return ;
	}
	int x_start = getHalfWidth(maxWidth, GET_BOARD_WIDTH(4, 8) + GET_BOARD_WIDTH(5, 8) + margin);
	if (x_start == 0)
		x_start = 2;
	display_game_board(game, y_margin + margin / 3, x_start, GRID_SIZE_4, 8);
	if (higlight == GRID_SIZE_4)
		draw_border(game->main_w, y_margin + margin / 3, x_start , 8 * GRID_SIZE_4, COLOR_GREEN);
	y_margin += (maxWidth < 80) ? (GET_BOARD_HEIGHT(4, 8) + margin) : 0;
	x_start += (maxWidth < 80) ? 0 : GET_BOARD_WIDTH(5, 7);
	display_game_board(game, y_margin, x_start, GRID_SIZE_5, 8);
	if (higlight == GRID_SIZE_5)
		draw_border(game->main_w, y_margin, x_start, 8 * GRID_SIZE_5, COLOR_GREEN);
	wattroff(game->main_w, A_REVERSE);
}

int	displayCenteredMsg(WINDOW *win, int y_margin, int maxWidth, char *msg)
{
	int x_start = getHalfWidth(maxWidth, ft_strlen(msg));
	mvwprintw(win, y_margin, x_start, "%s", msg);
	return (1);
}

void    displayGameTitle(WINDOW *win, e_titleType type, int maxWidth, int y_pading)
{
    int maxLength = getMaxLengthWchar_t(titles[type].titleText);
    int marginLeft = getHalfWidth(maxWidth, maxLength);
    for (unsigned long i = 0; titles[type].titleText[i] != NULL; i++)
    {
        wattron(win, COLOR_PAIR(0) | A_BOLD | A_DIM);
        mvwaddwstr(win, i + y_pading, marginLeft, titles[type].titleText[i]);
    }
}

