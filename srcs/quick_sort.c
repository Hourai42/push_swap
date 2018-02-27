/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 01:45:58 by ttran             #+#    #+#             */
/*   Updated: 2018/02/26 01:45:58 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void    ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int     partition(int *arr, int low, int high)
{
	int pivot;
	int i;

	i = (low - 1);
	pivot = arr[high];
	while (low <= (high - 1))
	{
		if (arr[low] <= pivot)
			ft_swap(&arr[++i], &arr[low]);
		low++;
	}
	ft_swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/*
** Low is the starting index, high is the ending index.
** Give this one a bit of practice and understanding, it seems useful.
*/

static void    quicksort(int *arr, int low, int high)
{
	int partit;

	if (low < high)
	{
		partit = partition(arr, low, high);
		quicksort(arr, low, partit - 1);
		quicksort(arr, partit + 1, high);
	}
}

static void    handle_pos(int *arr, t_control *a)
{
	t_stack *ptr;
	int i;

	i = 0;
	ptr = a->top;
	while (ptr != NULL)
	{
		while (ptr->nbr != arr[i])
			i++;
		ptr->pos = i + 1;
		i = 0;
		ptr = ptr->down;
	}
}

void    set_pos(t_control *a, int num)
{
	int *arr;
	t_stack *ptr;
	int i;

	i = 0;
	ptr = a->top;
	arr = malloc(sizeof(int) * num);
	while (ptr != NULL)
	{
		arr[i++] = ptr->nbr;
		ptr = ptr->down;
	}
	quicksort(arr, 0, num - 1);
	handle_pos(arr, a);
	free(arr);
}
