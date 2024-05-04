/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:09:34 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 16:46:57 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"

/*
 * dir = 'r' || 'l'
 */
void	merge(int *array, int size, int dir)
{
	int	merged_array[size];
	int	last_num = -1;
	int	last_num_pos = -1;
	int	merged_count = 0;

	for (int i = 0; i < size; i++)
		merged_array[i] = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] != 0)
		{
			if (last_num == array[i])
			{
				/**
				 * If last num is the same as current number, so we can merge
				 * two numbers. New number would be created
				 */
				merged_array[merged_count] = last_num * 2;
				merged_count++;
			}
			else if (count(array, size, array[i]) % 2 != 0)
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
			}
			last_num = array[i];
			last_num_pos = i;
		}
	}
	if (dir == 'r')
		right_align(merged_array, size, merged_count);
	for (int i = 0; i < size; i++)
		array[i] = merged_array[i];
}
