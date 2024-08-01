
#include "../inc/tui_bonus.h"
#include <wchar.h>

int	set_random_nbr(t_game *game, int nbr)
{
	int	empty_cells[MAX_SIZE * MAX_SIZE][2];
	int	i = 0;
	int	size = 0;
	size = game->grid;

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (game->board[row][col] == 0)
			{
				i++;
				empty_cells[i - 1][0] = row;
				empty_cells[i - 1][1] = col;
			}
		}
	}
	if (i == 0)
		return (1);
	int n = rand() % i;
	int r = empty_cells[n][0];
	int c = empty_cells[n][1];
	game->board[r][c] = nbr;
	return (0);
}

int get_random_nbr(void)
{
	int	nbr = rand() % 100;
	if (nbr < 90)
		return (2);
	else
		return (4);
}

int	intlen(int value)
{
	int	n = 0;

	while (value > 0)
	{
		value /= 10;
		n++;
	}
	return (n);
}

int	is_power_two(int value)
{
	if (value <= 0)
		return (0);
	return ((value & (value - 1)) == 0);
}

int	get_power(int value)
{
	int result = 1;
	int i = 0;
	if (value <= 0 || value > 2048)
		return (0);
	while (result < value)
	{
		result *= 2;
		i++;
	}
	return (i);
}

int getMaxLengthWchar_t(wchar_t **arr)
{
    int k = 0;
    for (int i = 0; arr[i] != NULL; i++)
    {
        int tmp = 0;
        while (arr[i][tmp] != 0)
            tmp++;
        if (tmp > k)
            k = tmp;
    }
    return (k);
}

int getArrSize(wchar_t **arr)
{
	int i = 0;
    for (; arr[i] != NULL; i++) {}
    return (i);
}

int	get_box_width(int win_x)
{
	int w_x = win_x - 1;
	if (w_x > 105)
		w_x = 104;
	return (w_x * 0.5);
}

int getHalfWidth(int maxWidth, int elemLength)
{
	if (maxWidth <= elemLength)
		return (0);
	return (maxWidth - (maxWidth * 0.5) - (elemLength / 2));
}

