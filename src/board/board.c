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
#include "../../lib/libft/libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

t_BoardState	*initialize_board(int size)
{
	if (size < 4 || size > 5)
	{
		ft_putnbr_lft_fd(__LINE__, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(__FILE__, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(ERR_INVALID_BOARD_SIZE, 2);
		return (NULL);
	}

	t_BoardState	*brd = malloc(sizeof(t_BoardState));
	if (!brd)
	{
		ft_putnbr_lft_fd(__LINE__, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(__FILE__, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		return (NULL);
	}
	brd->size = size;
	brd->move = 0;

	brd->board = malloc(sizeof(int *) * brd->size);
	if (!brd->board)
	{
		ft_putnbr_lft_fd(__LINE__, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(__FILE__, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		return (NULL);
	}
	for (int y = 0; y < size; y++)
	{
		brd->board[y] = malloc(sizeof(int) * brd->size);
		if (!brd->board[y])
		{
			ft_putnbr_lft_fd(__LINE__, 2);
			ft_putstr_fd(":", 2);
			ft_putstr_fd(__FILE__, 2);
			ft_putstr_fd(" - ", 2);
			ft_putendl_fd(ERR_MALLOC_FAIL, 2);
			return (NULL);
		}
		for (int x = 0; x < size; x++)
			brd->board[y][x] = 0;
	}
	return (brd);
}

void	destroy_board(t_BoardState *brd)
{
	if (!brd || !brd->board)
		return ;
	for (int y = 0; y < brd->size; y++)
	{
		if (brd->board[y])
			ft_free_ptr(brd->board[y]);
	}
	if (brd->board)
		ft_free_ptr(brd->board);
	if (brd)
		ft_free_ptr(brd);
}

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
