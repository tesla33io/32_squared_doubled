/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:28:41 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/03 22:47:54 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../lib/libft/libft.h"

# include <ncurses.h>
# include <stdbool.h>

/* DEFINES & STRUCTS */

/* Error messages */

# define ERR_INVALID_BOARD_SIZE "Error: invalid board size"
# define ERR_MALLOC_FAIL "Error: memory allocation failed"

/* Board related stuff */

typedef struct s_BoardState
{
	int		size; /* 4 or 5 */
	int		move;
	int		**board;
//	t_deque	*gc; /* List of pointers for custom GC system */
}	t_BoardState;

enum e_const
{
	WIN_VALUE = 2048
};

/* ncurses settings */

typedef struct s_GameState
{
	bool	in_menu_state;
	WINDOW	*win;
	int		win_height;
	int		win_width;
}	t_GameState;

/* FUNCTIONS */

t_BoardState	*initialize_board(int size);
void			destroy_board(t_BoardState *brd);

t_GameState		*initialize_game(void);
void			destroy_game(t_GameState *game);

#endif /* GAME_H */
