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

void	decide_bottom(int numbot, t_control *a, t_control *b, int perfect)
{
	int tmpperfect;

	if (perfect == 0)
		tmpperfect = 0;
	else
		tmpperfect = perfect - 1;
	while (perfect - 1 > 0)
	{
		op_rrr(a, b);
		ft_printf("%s%s", PURPLE, "rrr\n");
		perfect--;
	}
	while (numbot - tmpperfect > 0)
	{
		op_rra(b);
		ft_printf("%s%s", LIME, "rrb\n");
		numbot--;
	}
}

void	decide_top(int numtop, t_control *a, t_control *b, int perfect)
{
	int tmpperfect;

	tmpperfect = perfect;
	if (numtop == 1)
	{
		numtop--;
		if (perfect > 0)
		{
			op_ra(a);
			ft_putstr("ra\n");
		}
	}
	else
	{
		while (perfect > 0)
		{
			op_rr(a, b);
			ft_printf("%s%s", DARKYELLOW, "rr\n");
			perfect--;
		}
	}
	while (numtop - tmpperfect > 0)
	{
		op_ra(b);
		ft_printf("%s%s", CYAN, "rb\n");
		numtop--;
	}
}

void    placement(t_control *a, t_control *b)
{
	op_pa(b, a);
	ft_printf("%s%s", MAGENTA, "pb\n");
}

int		setup_placement(t_control *a, t_control *b, int perfect)
{
	int decide;

	if ((decide = up_or_down(a, b)) != 0)
	{
		if (decide < 0)
		{
			decide_bottom(decide * -1, a, b, perfect);
			return (-1);
		}
		decide_top(decide, a, b, perfect);
		return (1);
	}
	return (0);
}

int		sizeof_stack(t_control *a)
{
	t_stack *ptr;
	int i;

	i = 0;
	ptr = a->top;
	while (ptr != NULL)
	{
		i++;
		ptr = ptr->down;
	}
	return (i);
}

/*
** Negative signals you're grabbing lower pieces.
*/

int		calc_units_inbtwn(int iterations, int size_a)
{
	double size_a_round;
	int size_a_up;

	size_a_round = (double)size_a;
	size_a_up = (int)(size_a_round / 2 + 0.5);
	if (iterations <= size_a_up)
		return (iterations);
	else
		return ((size_a - iterations) * -1);
}

void	set_perfect_mod(t_h *h, int moves)
{
	if (moves < 0 && h->simultaneous <= 0)
	{
		moves = (moves * -1);
		h->simultaneous *= -1;
		if (moves >= h->simultaneous)
			h->perfect = h->simultaneous * -1;
		else
			h->perfect = moves * -1; 
	}
	else if (moves >= 0 && h->simultaneous >= 0)
	{
		if (moves >= h->simultaneous)
			h->perfect = h->simultaneous;
		else
			h->perfect = moves;
	}
	else
		h->perfect = 0;
}

/*
** Going down = RRA. Two negatives = shared
** Going up = RA.  Two positives = shared
** Value is the median - pos, if it's negative then it's *-1 +1.
** Iterations is how many iteration is in between. 
** Simultaneous sees if the setup can cut into the movement.
*/

int	calc_heuristic(int value, int iterations, t_h *h)
{
	int heuristic;

	set_perfect_mod(h, iterations);
	if (value < 0)
		value = (value * -1);
	if (iterations < 0 && h->perfect <= 0)
		heuristic = value + (iterations * -1 + 1) - (h->perfect * -1);
	else if (iterations >=0 && h->perfect >= 0)
		heuristic = value + iterations - h->perfect;
	else
	{
		if (iterations < 0)
			iterations = (iterations * -1) + 1;
		heuristic = value + iterations;
	} 
	return (heuristic);
}

void	make_movements(int moves, t_h *h, t_control *a)
{
	if (moves < 0)
	{
		moves *= -1;
		moves++;
		while (moves - h->perfect > 0)
		{
			op_rra(a);
			ft_printf("%s%s", GREEN, "rra\n");
			moves--;
		}
	}
	else if (moves > 0)
	{
		while (moves - h->perfect > 0)
		{
			op_ra(a);
			ft_printf("%s%s", LIGHTBLUE, "ra\n");
			moves--;
		}
	}
}

void	set_perfect(t_h *h, int moves)
{
	if (moves < 0 && h->simult <= 0)
	{
		moves = (moves * -1 + 1);
		h->simult *= -1;
		if (moves >= h->simult)
			h->perfect = h->simult;
		else
			h->perfect = moves; 
	}
	else if (moves >= 0 && h->simult >= 0)
	{
		if (moves >= h->simult)
			h->perfect = h->simult;
		else
			h->perfect = moves;
	}
	else
		h->perfect = 0;
}

int		up_or_down_mod(t_stack *a, t_control *b)
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
	if (size_b != 0 && size_b != 1 && (a->nbr < b->top->nbr && a->nbr > b->bottom->nbr))
	{
		ptr = b->top;
		while (ptr != NULL)
		{
			if (a->nbr > ptr->nbr)
				i++;
			ptr = ptr->down;
		}
	}
	return (up_or_down_decide(i, size_b)); 
}

/*
** See the difference with or without the >= on the heuristic. Meaning do you prioritize low iterations or high iterations?
** Ughh, you idiot. You have to remake the thing for h->simultaneous...
** FUUUUUUCKKKK AAAARRRGHHHh
*/

void	movement(t_control *a, t_control *b, t_h *h, int median)
{
	t_stack *ptr;
	int size_a;
	int moves;

	size_a = sizeof_stack(a);
	ptr = a->top;
	h->simultaneous = up_or_down_mod(ptr, b);
	if (ptr != NULL)
		h->heuristic = calc_heuristic(median - ptr->pos, calc_units_inbtwn(h->counter, size_a), h);
	while (ptr != NULL)
	{
		h->simultaneous = up_or_down_mod(ptr, b);
		h->heuristictmp = calc_heuristic(median - ptr->pos, calc_units_inbtwn(h->counter, size_a), h);
		if (h->heuristic > h->heuristictmp)
		{
			h->pos = h->counter;
			h->heuristic = h->heuristictmp;
		}
		ptr = ptr->down;
		h->counter++;
	}
	moves = calc_units_inbtwn(h->pos, size_a);
	set_perfect(h, moves);
	make_movements(moves, h, a);
}

void	set_h(t_h **h)
{
	*h = malloc(sizeof(t_h));
	(*h)->heuristic = 0;
	(*h)->heuristictmp = 0;
	(*h)->counter = 0;
	(*h)->pos = 0;
	(*h)->simultaneous = 0;
	(*h)->simult = 0;
	(*h)->perfect = 0;
}

void	reset_h(t_h *h)
{
	h->heuristic = 0;
	h->heuristictmp = 0;
	h->counter = 0;
	h->pos = 0;
	h->simultaneous = 0;
	h->simult = 0;
	h->perfect = 0;
}

/*
** Well, let's just cram a movement + heuristic into here without a care in the world.
** Heuristic = you take the lowest value as the best.
** (median - pos), (if (< 0) then *-1 and +1), then plus steps - (same setup steps)
** Meaning you need to keep track if the *-1 +1 flag is triggered
** So that you can subtract the same setup steps only in the case that neg. steps are required.
** Then eventually, you can do something clever for the cleanup placement helping the next movement.
** Perhaps NO setup heuristic would be ideal.
** If you add setup, it'll never place things in the middle until the end if it misses it.
** Ie. skips a middle and places something over it, and now it's (n * 2) + 1 or (n * 2 + 2) more steps.
** Eh, (median - pos) + iterations - simultaneous movement, no setup included.
** Hmm, but your shit doesnt' assume a sorted stack B. Why isn't... FUCK.
*/

void    large_sort(t_control *a, t_control *b, int num)
{
	int clean;
	t_h *h;
	int median;

	median = num / 2;
	set_h(&h);
	set_pos(a, num);
	while (a->top != NULL)
	{
		movement(a, b, h, median);
		clean = setup_placement(a, b, h->perfect);
		placement(a, b);
		cleanup_placement(a, b, clean, median);
		reset_h(h);
	}
	fuck_it_all(a, b);
	// Free t_h heuristic;
}
