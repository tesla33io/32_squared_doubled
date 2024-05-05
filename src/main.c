/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:17:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/05 19:00:20 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h> /* DELETE */

int main()
{	
	int	size = 4;

	int	**brd = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		brd[i] = malloc(sizeof(int) * size);
	}
	brd[0] = (int []) {4,  2,  4, 8};
	brd[1] = (int []) {2,  4,  8, 2};
	brd[2] = (int []) {8, 16,  2, 4};
	brd[3] = (int []) {0,  0,  0, 0};
	
	bool mleft = moves_left(brd, size, 'd');
	printf(mleft ? "There are moves left\n" : "No moves left!\n");
	printf("\tOriginal:\n");
	
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\033[32;1m\t%d\033[0m", brd[i][j]);
		printf("|\n");
	}
/*
	char	dir = 'l';

	int	score = 0;

	score += update_board((int **) brd, size, dir);

	printf("\tAfter move (%c):\n", dir);
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\033[33;1m\t%d\033[0m", brd[i][j]);
		printf("|\n");
	}

	printf("Score: %d\n", score);
*/
	return (0);
}
