/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:59:29 by ttran             #+#    #+#             */
/*   Updated: 2018/02/17 18:59:30 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
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
		ft_printf("%s%s", PINK, "pb\n");
	}
}
*/

/*
void	closer_to_top(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		op_ra(a);
		ft_printf("%s%s", LIME, "ra\n");
	}
}	

void	closer_to_bottom(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		op_rra(a);
		ft_printf("%s%s", MAGENTA, "rra\n");
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
	ft_printf("%s%s", YELLOW, "pb\n");
}

int	ted_sort(t_control *a, t_control *b)
{
	int numNbrs;

	if (check_sorted(a, b) == 1)
		return (1);
	numNbrs = num_of_nbrs(a);
	while (numNbrs > 2)
	{
		find_and_push(a, b, numNbrs);
		numNbrs--;
	}
	if (a->top->nbr > a->bottom->nbr)
	{
		op_sa(a);
		ft_printf("%s%s", PURPLE, "sa\n");
	}
	fuck_it_all(a, b);
	return (1);
}
*/
/*
int		check_single_sorted(t_control *a)
{
	t_stack *ptr;

	ptr = a->top;

	while (ptr->down != NULL)
	{
		if (ptr->nbr > ptr->down->nbr)
			return (0);
		ptr = ptr->down;
	}
	return (1);
}

int	closer_to_top(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		if (check_single_sorted(a) == 1)
			return (1);
		if (a->top->nbr > a->top->down->nbr)
		{
			op_sa(a);
			ft_printf("%s%s", PURPLE, "sa\n");
		}
		else
		{
			op_ra(a);
			ft_printf("%s%s", MAGENTA, "rra\n");
		}
	}
	return (0);
}

int	closer_to_bottom(t_control *a, int smallest)
{
	while (a->top->nbr != smallest)
	{
		if (check_single_sorted(a) == 1)
			return (1);
		if (a->top->nbr > a->top->down->nbr)
		{
			op_sa(a);
			ft_printf("%s%s", PURPLE, "sa\n");
		}
		else
		{
			op_rra(a);
			ft_printf("%s%s", LIME, "rra\n");
		}
	}
	return (0);
}

int		find_and_push(t_control *a, t_control *b, int digits)
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
			pos = i;
			ptr = ptr2;
		}
		ptr2 = ptr2->down;
		i++;
	}
	if (pos <= digits/2 + 1)
	{
		if (closer_to_top(a, ptr->nbr) == 1)
			return (1);
	}
	else
		if (closer_to_bottom(a, ptr->nbr) == 1)
			return (1);
	op_pa(b, a);
	ft_printf("%s%s", YELLOW, "pb\n");
	return (0);
}

int		ted_sort(t_control *a, t_control *b)
{
	int numnbrs;

	if (check_sorted(a, b) == 1)
		return (1);
	numnbrs = num_of_nbrs(a);
	while (42)
		if (find_and_push(a, b, numnbrs--) == 1 || numnbrs == 2)
			break;
	if (a->top->nbr > a->bottom->nbr)
	{
		op_sa(a);
		ft_printf("%s%s", PURPLE, "sa\n");
	}
	fuck_it_all(a, b);
	return (1);
}
*/

/*
int main(int argc, char **argv)
{
	t_control *a;
	t_control *b;

	init_control(&a);
	init_control(&b);
	if (argc == 2)
	{
		if (parse_nbrs(argv[1], a) == 0)
		{
			ft_putstr(RED);
			write(2, "Error\n", 6);
		}
		else
			ted_sort(a, b);
	}
	check_stack(a);
	check_stack(b);
	//Free A and B!! And info!...
	return(0);
}
*/