/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:17:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 00:00:50 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <ncurses.h>

int main()
{	
	t_GameState		*game = initialize_game();
	if (!game)
		return (-1);
	t_BoardState	*brd = initialize_board(4);
	if (!brd)
		return (-2);
	display_board(brd, game);
	wgetch(game->win);
	destroy_board(brd);
	destroy_game(game);
	return (0);
}
