/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:17:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/05 14:07:59 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../lib/libft/libft.h"

#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h> /* DELETE */

int main(/*int ac, char *av[]*/)
{	
	int	size = 4;

	int	**brd = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		brd[i] = malloc(sizeof(int) * size);
	}
	brd[0] = (int []) {0,  2, 0, 2};
	brd[1] = (int []) {4,  2, 2, 4};
	brd[2] = (int []) {8, 16, 8, 0};
	brd[3] = (int []) {8,  0, 2, 2};

	printf("\tOriginal:\n");
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\033[32;1m\t%d\033[0m", brd[i][j]);
		printf("|\n");
	}

	char	dir = 'd';

	update_board((int **) brd, size, dir);

	printf("\tAfter move (%c):\n", dir);
	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j < size; j++)
			printf("\033[33;1m\t%d\033[0m", brd[i][j]);
		printf("|\n");
	}

	return (0);
}
