/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:21:33 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/05 18:58:26 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/tui_bonus.h"
#include "../../lib/libft/libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

static	int	count_moves(int *row, int size);

bool	moves_left(int **brd, int size, char dir)
{
	int	mleft = 0;
	for (int y = 0; y < size; y++)
	{
		if (dir == 'u' || dir == 'd')
		{
			int	*row = column_to_row(brd, size, y);
			if (dir == 'd')
				reverse_array(row, size);

			mleft += count_moves(row, size);

			if (dir == 'd')
				reverse_array(row, size);

			row_to_column(brd, row, size, y);
			continue ;
		}
		if (dir == 'r')
			reverse_array(brd[y], size);

		mleft += count_moves(brd[y], size);

		if (dir == 'r')
			reverse_array(brd[y], size);
	}
	return (mleft > 0);
}

bool	has_win_condition(int **brd, int size, int win)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (win != 0 && brd[y][x] == win)
				return (true);
		}
	}
	return (false);
}

static	int	count_moves(int *row, int size)
{
	int	moves = 0;
	int	empty_inside = 0;
	for (int i = 0; i < size; i++)
		moves += is_mergeable(row, size, i) ? 1 : 0;
	for (int j = 0; j < size - 1; j++)
	{
		if (row[j] == 0 && row[j + 1] != 0)
			empty_inside += 1;
	}
	moves += empty_inside;
	return (moves);
}
