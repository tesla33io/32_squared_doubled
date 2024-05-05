/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:21:33 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/03 23:43:52 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../lib/libft/libft.h"

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
