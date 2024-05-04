/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:17:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 19:59:05 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h> /* DELETE */

int main(/*int ac, char *av[]*/)
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

	int	size = 4;
	/*if (ac - 1 != size)
		return (printf("wtf?!\n"));
	int row[5] = {atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4]), atoi(av[5])};*/
	/*int	brds[4][4] = {
		{0,  2, 0, 2},
		{4,  2, 2, 4},
		{8, 16, 8, 0},
		{8,  0, 2, 2}
	};*/

	int	**brd = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		brd[i] = malloc(sizeof(int) * size);
	}
	brd[0] = (int []) {0,  2, 0, 2};
	brd[1] = (int []) {4,  2, 2, 4};
	brd[2] = (int []) {8, 16, 8, 0};
	brd[3] = (int []) {8,  0, 2, 2};

	printf("Original:\n");
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\t%d", brd[i][j]);
		printf("|\n");
	}

	update_board((int **) brd, size, 'r');

	printf("Move to the left:\n");
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\t%d", brd[i][j]);
		printf("|\n");
	}

	return (0);
}
