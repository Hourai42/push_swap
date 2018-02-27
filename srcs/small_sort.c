/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 01:19:26 by ttran             #+#    #+#             */
/*   Updated: 2018/02/22 01:19:28 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	num_of_nbrs(t_control *a)
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

void	fuck_it_all(t_control *a, t_control *b)
{
	while (b->top != NULL)
	{
		op_pa(a, b);
		//ft_printf("%s%s", PINK, "pa\n");
		ft_putstr("pa\n");
	}
}

void	closer_to_top(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		op_ra(a);
		//ft_printf("%s%s", LIME, "ra\n");
		ft_putstr("ra\n");
	}
}	

void	closer_to_bottom(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		op_rra(a);
		//ft_printf("%s%s", MAGENTA, "rra\n");
		ft_putstr("rra\n");
	}
}

void	find_and_push(t_control *a, t_control *b, int num)
{
	int i;
	int pos;
	t_stack *ptr;
	t_stack *ptr2;

	i = 1;
	pos = 1;
	ptr = a->top;
	ptr2 = a->top;
	while (ptr2 != NULL)
	{
		if (ptr->nbr > ptr2->nbr)
		{
			ptr = ptr2;
			pos = i;
		}
		ptr2 = ptr2->down;
		i++;
	}
	if (pos <= num/2 + 1)
		closer_to_top(a, ptr->nbr);
	else
		closer_to_bottom(a, ptr->nbr);
	op_pa(b, a);
	//ft_printf("%s%s", YELLOW, "pb\n");
	ft_putstr("pb\n");
}

void	small_sort(t_control *a, t_control *b, int num)
{
	while (num > 2)
	{
		find_and_push(a, b, num);
		num--;
	}
	if (a->top->nbr > a->bottom->nbr)
	{
		op_sa(a);
		//ft_printf("%s%s", PURPLE, "sa\n");
		ft_putstr("sa\n");
	}
	fuck_it_all(a, b);
}