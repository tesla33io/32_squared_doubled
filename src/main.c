#include "../inc/tui_bonus.h"
#include <ncurses.h>
#include <unistd.h>

static int	win_init(t_game *game);

int	main (void)
{
	t_game	game;
	setlocale(LC_ALL, "");

	if (win_init(&game) != 0)
		return (1);
	if (init_colors() != 0)
		return (1);
	game.board = NULL;
	launch_game(&game);
	return (0);
}

static int	win_init(t_game *game)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	mousemask(0, NULL);
	refresh();
	getmaxyx(stdscr, game->y_max, game->x_max);
	game->menu = true;
	game->main_w = newwin(game->y_max, game->x_max, 0, 0);
	return (0);
}

int	launch_game(t_game *game)
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
	if (game->menu)
		game_init(game);
	game_loop(game);
	return (0);
}

void	game_loop(t_game *game)
{
	game->menu = false;
	game->dir = '0';
	while (1)
	{
		update_game_board(game);
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
	update_game_board(game);
	return (0);
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
	for (int i = 0; i < size; i++)
	{
		game->board[i] = ft_malloc(NULL, sizeof(int) * size);
		if (!game->board[i])
		{
			ft_free_ptr(game->board);
			endwin();
			return ;
		}
		for (int j = 0; j < size; j++)
			game->board[i][j] = 0;
	}
	// if (is_power_two(WIN_VALUE) == 1)
	// 	game->win_value = WIN_VALUE;
	// else
	// 	game->win_value = 0;
	game->score = 0;
	game->max_score = 0;
	set_random_nbr(game, 2);
	set_random_nbr(game, 2);
	update_game_board(game);
}




