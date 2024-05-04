/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:17:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 17:11:32 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h> /* DELETE */

int main(int ac, char *av[])
{	
	/*t_GameState		*game = initialize_game();
	if (!game)
		return (-1);
	t_BoardState	*brd = initialize_board(4);
	if (!brd)
		return (-2);
	display_board(brd, game);
	wgetch(game->win);
	destroy_board(brd);
	destroy_game(game);*/

	(void)ac;

	int	size = 4;
	int row[4] = {atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4])};

	printf("Original:\t");
	for (int i = 0; i < size; i++)
		printf("\t%d", row[i]);
	printf("\n");

	merge(row, size, 'r');
	
	printf("Merged:\t\t");
	for (int i = 0; i < size; i++)
		printf("\t%d", row[i]);
	printf("\n");

	return (0);
}
