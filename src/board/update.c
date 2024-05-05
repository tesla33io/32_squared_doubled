/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:09:34 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/05 17:42:08 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"

/*
 * dir:
 *  - r for right
 *  - l for left
 *  - u for up
 *  - d for down
 */
int	update_board(int **array, int size, int dir)
{
	if (dir == '0')
		return (0);
	int	move_score = 0;
	for (int y = 0; y < size; y++)
	{
		if (dir == 'u' || dir == 'd')
		{
			// vertical move (tricky)
			// if down - reverse array
			int	*row = column_to_row(array, size, y);
			if (dir == 'd')
				reverse_array(row, size);

			move_score += merge(row, size);

			if (dir == 'd')
				reverse_array(row, size);

			row_to_column(array, row, size, y);
			continue ;
		}
		if (dir == 'r')
			reverse_array(array[y], size);

		move_score += merge(array[y], size);

		if (dir == 'r')
			reverse_array(array[y], size);
	}
	return (move_score);
}

int	merge(int *array, int size)
{
	int	merged_array[size];
	int	last_num = -1;
	int	last_num_pos = -1;
	int	merged_count = 0;
	int	row_score = 0;

	for (int i = 0; i < size; i++)
		merged_array[i] = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] != 0)
		{
			if (array[i] == last_num)
			{
				/**
				 * If last num is the same as current number, so we can merge
				 * two numbers. New number would be created
				 */
				row_score += array[i] * 2;
				merged_array[merged_count] = array[i] * 2;
				merged_count++;
				array[i] = 0;
				array[last_num_pos] = 0;
			}
			else if (count(array, size, array[i]) < 2)
			{
				/**
				 * If the occurences of the number is not even
				 * that means that this num cannot be merged and
				 * we can just add it to the merged array
				 */
				merged_array[merged_count] = array[i];
				merged_count++;
			}
			else if (!is_mergeable(array, size, i))
			{
				merged_array[merged_count] = array[i];
				merged_count++;
				array[i] = 0;
			}
			last_num = array[i];
			last_num_pos = i;
		}
	}
	for (int i = 0; i < size; i++)
		array[i] = merged_array[i];
	return (row_score);
}
