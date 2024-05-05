/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:33:09 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/03 22:47:12 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <stdlib.h>
#include <ncurses.h>

t_GameState	*initialize_game(void)
{
	t_GameState	*game = malloc(sizeof(t_GameState));
	if (!game)
	{
		ft_putnbr_lft_fd(__LINE__, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(__FILE__, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		return (NULL);
	}
	
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, game->win_height, game->win_width);

	game->win = newwin(game->win_height, game->win_width, 0, 0);
	box(stdscr, 0, 0);
	keypad(game->win, TRUE);
	refresh();

	return (game);
}

void	destroy_game(t_GameState *game)
{
	if (game->win)
		delwin(game->win);
	endwin();
	if (game)
		ft_free_ptr(game);
}
