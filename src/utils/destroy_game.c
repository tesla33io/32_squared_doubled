
#include "../lib/libft/libft.h"

void	destroy_board(int **brd, int size)
{
	for (int y = 0; y < size; y++)
	{
		if (brd[y])
			ft_free_ptr(brd[y]);
	}
	ft_free_ptr(brd);
}
