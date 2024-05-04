/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:51:54 by astavrop          #+#    #+#             */
/*   Updated: 2024/05/04 18:09:14 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * Counts the occurrences of a given integer in an array.
 *
 * This function iterates through the elements of the array and counts the
 * occurrences of the specified integer 'n'.
 *
 * @param array Pointer to the integer array.
 * @param size The number of elements in the array.
 * @param n The integer whose occurrences need to be counted.
 * @return The count of occurrences of 'n' in the array.
 */
int	count(int *array, int size, int n)
{
	int	c = 0;

	for (int i = 0; i < size; i++)
	{
		if (array[i] == n)
			c++;
	}
	return (c);
}

/**
 * Right aligns elements in an integer array up to a specified index.
 *
 * This function right aligns the elements in the array up to the specified index 'last'.
 * It shifts elements towards the end of the array until 'last', and sets the previous
 * positions to 0.
 *
 * @param array Pointer to the integer array to be modified.
 * @param size The number of elements in the array.
 * @param last The index up to which elements will be right aligned.
 */
void	right_align(int *array, int size, int last)
{
	if (last == size)
		return ;
	for (int i = 0; i < last; i++)
	{
		array[size - i - 1] = array[last - i - 1];
		array[last - i - 1] = 0;
	}
}

bool	is_mergeable(int *array, int size, int index)
{
	int	target_val = array[index];

	if (index + 1 >= size)
		return (false);
	for (int i = index + 1; i < size && array[i] != target_val; i++)
	{
		if (array[i] != 0 && array[i] != target_val)
			return (false);
	}
	return (true);
}

void	reverse_array(int *array, int size)
{
	int	tmp;
	for (int i = 0; i < (int) (size / 2); i++)
	{
		tmp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = tmp;
	}
}
