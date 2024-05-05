/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:45:50 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 00:13:13 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../lib/libft/libft.h"

#include <ncurses.h>

void	display_board(t_BoardState *brd, t_GameState *game)
{
	if (!brd || !game)
	{
		ft_putnbr_lft_fd(__LINE__, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(__FILE__, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(ERR_UNDEF_BOARD_OR_GAME, 2);
		return ;
	}

	int	start_y = game->win_height / brd->size;
	int	start_x = game->win_width / brd->size;

	for (int y = 0; y < brd->size; y++)
	{
		for (int ul = 0; ul < start_x + (brd->size * 20); ul++)
			mvwprintw(game->win, start_y - 1, start_x - 1 + ul, "=");
		for (int x = 0; x < brd->size; x++)
		{
			mvwprintw(game->win, start_y + (y * 10), start_x + (x * 40),
					"| %d", brd->board[y][x]);
			for (int vl = 0; vl < start_y + (y * 10); vl++)
			{
				mvwprintw(game->win, start_y + (y * 10) + vl, start_x + (x * 40),
						"|");
			}
		}
		if (brd->size > y)
		{
			for (int ul = 0; ul < start_x + (brd->size * 20); ul++)
				mvwprintw(game->win, start_y - 1 + (y * 10), start_x - 1 + ul, "=");
		}
	}
}
