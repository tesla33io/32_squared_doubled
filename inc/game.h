/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:28:41 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/05 14:00:47 by astavrop         ###   ########.fr       */
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
# define ERR_UNDEF_BOARD_OR_GAME "Error: board or game is undefined"

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

void			display_board(t_BoardState *brd, t_GameState *game);

void			update_board(int **array, int size, int dir);
void			merge(int *array, int size);

/* Utils */

int				count(int *array, int size, int n);
void			right_align(int *array, int size, int last);
bool			is_mergeable(int *array, int size, int index);
void			reverse_array(int *array, int size);
int				*column_to_row(int **brd, int size, int column);
void			row_to_column(int **brd, int *row, int size, int column);

#endif /* GAME_H */
