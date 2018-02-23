/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 01:24:14 by ttran             #+#    #+#             */
/*   Updated: 2018/02/22 01:24:15 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
** Kept simple for now. Heuristic will only be used for seeing if it's worth
** it to do the double operations.
** In the future, possibly consider more than one digit for the heuristic
** and look at groups instead -- the operations that put most median to 
** the top. But that probably isn't worth it as each time you place a piece
** in, you have a ton of rotations to get a more fitting piece in. 
** How about swaps to get more fitting pieces in at the beginning?
** Hmm, the reverse and rotates should already do the trick for this...
** Through swaps, you could get rid of putting in undesirables early?
** Ie. since your double rotations will change the "front"
** You can swap to get rid of end/beginning pieces early on.
*/

void    ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int     partition(int *arr, int low, int high)
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

void    quicksort(int *arr, int low, int high)
{
	int partit;

	if (low < high)
	{
		partit = partition(arr, low, high);
		quicksort(arr, low, partit - 1);
		quicksort(arr, partit + 1, high);
	}
}

void    handle_pos(int *arr, t_control *a)
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

int     up_or_down_decide(int i, int size_b)
{
	double size_b_round;
	int size_b_up;

	size_b_round = (double)size_b;
	size_b_up = (int)(size_b_round / 2 + .5);
	if (i == 0 || i == size_b)
		return (0);
	if (i >= size_b_up)
		return (size_b - i);
	else
		return (i * -1);
}

int		up_or_down(t_control *a, t_control *b)
{
	int size_b;
	t_stack *ptr;
	int i;

	i = 0;
	size_b = 0;
	ptr = b->top;
	while (ptr != NULL)
	{
		size_b++;
		ptr = ptr->down;
	}
	if (size_b != 0 && size_b != 1 && (a->top->nbr < b->top->nbr && a->top->nbr > b->bottom->nbr))
	{
		ptr = b->top;
		while (ptr != NULL)
		{
			if (a->top->nbr > ptr->nbr)
				i++;
			ptr = ptr->down;
		}
	}
	return (up_or_down_decide(i, size_b)); 
}

void	decide_bottom(int numbot, t_control *b)
{
	while (numbot > 0)
	{
		op_rra(b);
		ft_printf("%s%s", LIME, "rrb\n");
		numbot--;
	}
}

void	decide_top(int numtop, t_control *b)
{
	if (numtop == 1)
		numtop--;
	while (numtop > 0)
	{
		op_ra(b);
		ft_printf("%s%s", CYAN, "rb\n");
		numtop--;
	}
}

int		clean_swap_heuristic(t_control *a, int median)
{
	int norm_median_top;
	int norm_median;

	if (a->top != NULL && a->top->down != NULL)
	{
		norm_median_top = a->top->pos - median;
		if (norm_median_top < 0)
			norm_median_top *= -1;
		norm_median = a->top->down->pos - median;
		if (norm_median < 0)
			norm_median *= -1;
		if (norm_median_top > norm_median)
			return (1);
	}
	return (0);
}

void	clean_top_rr(t_control *a, int iterations, int closest_to_middle)
{
	int put_back;

	put_back = iterations - closest_to_middle;
	while (put_back > 0)
	{
		op_ra(a);
		put_back--;
		ft_printf("%s%s", LIME, "rrb\n");
	}
	while (closest_to_middle > 0)
	{
		ft_printf("%s%s", PURPLE, "rrr\n");
		closest_to_middle--;
	}
}

void	clean_top_rr_heuristic(t_control *a, int median, int iterations)
{
	int tmpiter;
	int closest_to_middle;
	int norm_median;
	int norm_compare;

	closest_to_middle = 0;
	norm_median = a->top->pos - median;
	if (norm_median < 0)
		norm_median *= -1;
	tmpiter = 0;
	while (tmpiter < iterations)
	{
		op_rra(a);
		tmpiter++;
		norm_compare = a->top->pos - median;
		if (norm_compare < 0)
			norm_compare *= -1;
		if (norm_compare < norm_median)
		{
			closest_to_middle = tmpiter;
			norm_median = norm_compare;			
		}
	}
	clean_top_rr(a, iterations, closest_to_middle);
}

void	clean_top(t_control *a, t_control *b, int median)
{
	int i;

	i = 0;
	if (b->top->nbr < b->top->down->nbr)
	{
		if (clean_swap_heuristic(a, median) == 1)
		{
			op_tss(a, b);
			ft_printf("%s%s", BLUE, "ss\n");
		}
		else
		{
			op_tsa(b);
			ft_printf("%s%s", WHITE, "sb\n");
		}
	}
	while (b->top->nbr < b->bottom->nbr)
	{
		i++;
		op_rra(b);
	}
	if (a->top != NULL)
		clean_top_rr_heuristic(a, median, i);
}

void	clean_bot_r(t_control *a, int iterations, int closest_to_middle)
{
	int put_back;

	put_back = iterations - closest_to_middle;
	while (put_back > 0)
	{
		op_rra(a);
		put_back--;
		ft_printf("%s%s", CYAN, "rb\n");
	}
	while (closest_to_middle > 0)
	{
		ft_printf("%s%s", DARKYELLOW, "rr\n");
		closest_to_middle--;
	}
}

void	clean_bot_r_heuristic(t_control *a, int median, int iterations)
{
	int tmpiter;
	int closest_to_middle;
	int norm_median;
	int norm_compare;

	closest_to_middle = 0;
	norm_median = a->top->pos - median;
	if (norm_median < 0)
		norm_median *= -1;
	tmpiter = 0;
	while (tmpiter < iterations)
	{
		op_ra(a);
		tmpiter++;
		norm_compare = a->top->pos - median;
		if (norm_compare < 0)
			norm_compare *= -1;
		if (norm_compare < norm_median)
		{
			closest_to_middle = tmpiter;
			norm_median = norm_compare;			
		}
	}
	clean_bot_r(a, iterations, closest_to_middle);
}

void	clean_bot(t_control *a, t_control *b, int median)
{
	int i;

	i = 0;
	while (b->top->nbr < b->bottom->nbr)
	{
		i++;
		op_ra(b);
	}
	if (a->top != NULL)
		clean_bot_r_heuristic(a, median, i);
}

void    cleanup_placement(t_control *a, t_control *b, int clean, int median)
{
	if (b->bottom != NULL)
	{
		if (clean == 1)
			clean_top(a, b, median);
		else
			clean_bot(a, b, median);
	}
}

void    placement(t_control *a, t_control *b)
{
	op_pa(b, a);
	ft_printf("%s%s", MAGENTA, "pb\n");
}

int		setup_placement(t_control *a, t_control *b)
{
	int decide;

	if ((decide = up_or_down(a, b)) != 0)
	{
		if (decide < 0)
		{
			decide_bottom(decide * -1, b);
			return (-1);
		}
		decide_top(decide, b);
		return (1);
	}
	return (0);
}

void    large_sort(t_control *a, t_control *b, int num)
{
	int clean;

	set_pos(a, num);
	while (a->top != NULL)
	{
		clean = setup_placement(a, b);
		placement(a, b);
		cleanup_placement(a, b, clean, num / 2);
	}
	fuck_it_all(a, b);
	//Now, how should the heuristic work? You know about utilizing
	// rr, rrr, and double swaps.... 
	// You'll check and see if you can reach a more "middle" number
	// each time you do this. 
}
